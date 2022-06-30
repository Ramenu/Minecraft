#define GLM_ENABLE_EXPERIMENTAL // For built-in glm hash

#include "minecraft/world/chunkgenerator.hpp"
#include "minecraft/world/worldgen.hpp"
#if defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW64__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wduplicated-branches"
    #include "glm/gtx/hash.hpp"
    #pragma GCC diagnostic pop
#else
    #include "glm/gtx/hash.hpp"
#endif
#include <unordered_map>
#include "minecraft/camera/camera.hpp"
#include "minecraft/rendering/renderinfo.hpp"


namespace ChunkGenerator
{
    static ChunkMesh generateChunkMesh(const ChunkArray &terrain, const glm::i32vec3 &position) noexcept;
    static constexpr int PRELOAD_CHUNKS {1};

    bool finishedInitialization {false};
    std::unordered_map<glm::i32vec3, std::pair<ChunkData, std::uint8_t>> mappedBiomes;


    /**
     * Returns a chunk of the given biome and at the chunk offset
     * position specified.
     */
    static std::pair<ChunkData, std::uint8_t> initChunkData(Biome biome, const glm::i32vec3 &position) noexcept
    {
        auto terrain {WorldGen::generateTerrain(biome)};
        auto mesh {generateChunkMesh(terrain.first, position)};
        return {ChunkData{terrain.first, mesh, biome}, terrain.second};
    }

    /**
     * Creates chunks near the player's position,
     * where 'p' is the player's chunk offset.
     */
    static void createChunksNearPlayer(const glm::i32vec3 &p) noexcept
    {
        for (auto x {p.x - RENDER_DISTANCE_X - PRELOAD_CHUNKS}; x < p.x + RENDER_DISTANCE_X + PRELOAD_CHUNKS; ++x)
        {
            for (auto z {p.z - RENDER_DISTANCE_Z - PRELOAD_CHUNKS}; z < p.z + RENDER_DISTANCE_Z + PRELOAD_CHUNKS; ++z)
            {
                const glm::i32vec3 chunkOffset {x, 0, z};
                if (mappedBiomes.find(chunkOffset) == mappedBiomes.end())
                    mappedBiomes.insert({chunkOffset, initChunkData(Forest, chunkOffset)});

                const auto currentCameraOffset {Camera::getCameraPosChunkOffset()};

                // If the position of the player changes while adding new chunks, return immediately
                // so we can get the updated position the next time the function is called.
                if (currentCameraOffset.x != p.x || currentCameraOffset.z != p.z)
                    return;
            }
        }
    }

    /**
     * Generates the mesh of the chunk given the terrain layout 
     * and returns it. The position is just the offset of the chunk.
     */
    static ChunkMesh generateChunkMesh(const ChunkArray &terrain, const glm::i32vec3 &position) noexcept
    {
        ChunkMesh chunkVertices;

        // unfortunately, this can't be done at compile time because the vector is too big.
        // Tried this with std::array too, but didn't work. Let me know if this will be possible
        // for the compiler to do efficiently in a dozen years or so
        chunkVertices.meshAttributes[Attribute::Ambient] = {[]() noexcept {
            std::vector<float> amb (CHUNK_VOLUME * VERTICES_SIZES[Attribute::Ambient]);
            std::fill(amb.begin(), amb.end(), DEFAULT_AMBIENT_LEVEL);
            return amb;
        }()};

        const glm::i32vec3 worldCoords {position.x * CHUNK_WIDTH, position.y * CHUNK_HEIGHT, position.z * CHUNK_LENGTH};
        for (std::int32_t y {}; y < CHUNK_HEIGHT; ++y)
        {
            for (std::int32_t x {}; x < CHUNK_WIDTH; ++x)
            {
                for (std::int32_t z {}; z < CHUNK_LENGTH; ++z)
                {
                    const float xW {static_cast<float>(x + worldCoords.x)};
                    const float yW {static_cast<float>(y + worldCoords.y)};
                    const float yZ {static_cast<float>(z + worldCoords.z)};
                    const auto pos {createCubeAt(xW, yW, yZ)};
                    const auto blockId {getBlockIDVertices(terrain[x][y][z].name)};
                    chunkVertices.meshAttributes[Attribute::Position].insert(chunkVertices.meshAttributes[Attribute::Position].end(), 
                                                                            pos.begin(), 
                                                                            pos.end());
                    
                    chunkVertices.meshAttributes[Attribute::BlockID].insert(chunkVertices.meshAttributes[Attribute::BlockID].end(),
                                                                            blockId.begin(),
                                                                            blockId.end());

                }
            }
        }

        return chunkVertices;
    }


    /**
     * Initializes the chunk generator. Should be called
     * from a seperate thread. Runs in a continuous loop
     * generating chunks near the player, so when the game
     * is done running, make sure to set 'stopThread' to
     * true.
     */
    void init() noexcept 
    {
        #if 1
        createChunksNearPlayer(Camera::getCameraPosChunkOffset());

        finishedInitialization = true;
        while (!stopThread)
            createChunksNearPlayer(Camera::getCameraPosChunkOffset());
        #else
            auto data {initChunkData(Plains, {0, 0, 0})};
            mappedBiomes.insert({{0, 0, 0}, data});

            finishedInitialization = true;
        #endif
    }

    
    /**
     * Returns the specified biome's chunk data
     * (i.e., the mesh and terrain layout).
     */
    std::pair<ChunkData, std::uint8_t> retrieveChunk(const glm::i32vec3 &position) noexcept
    {
        auto data {std::move(mappedBiomes.at(position))}; // copying the data can be expensive so move it instead
        return data;
    }

    /**
     * Returns true if enough chunks have been
     * stockpiled around the player.
     */
    bool hasFinishedStockpiling() noexcept {
        return finishedInitialization;
    }
}