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
    static constexpr int PRELOAD_CHUNKS {1};
    static ChunkData initChunkData(Biome biome, const glm::i32vec3 &position) noexcept;

    bool finishedInitialization {false};
    std::unordered_map<glm::i32vec3, ChunkData> mappedBiomes;


    static void createChunksNearPlayer(const glm::i32vec3 &p) noexcept
    {
        for (auto x {p.x - RENDER_DISTANCE_X - PRELOAD_CHUNKS}; x < p.x + RENDER_DISTANCE_X + PRELOAD_CHUNKS; ++x)
        {
            for (auto z {p.z - RENDER_DISTANCE_Z - PRELOAD_CHUNKS}; z < p.z + RENDER_DISTANCE_Z + PRELOAD_CHUNKS; ++z)
            {
                const glm::i32vec3 chunkOffset {x, 0, z};
                if (mappedBiomes.find(chunkOffset) == mappedBiomes.end())
                    mappedBiomes.insert({chunkOffset, initChunkData(Plains, chunkOffset)});

                #if 0
                const auto currentCameraOffset {Camera::getCameraPosChunkOffset()};

                // If the position of the player changes while adding new chunks, return immediately
                // so we can get the updated position the next time the function is called.
                if (currentCameraOffset.x != p.x || currentCameraOffset.z != p.z)
                    return;
                #endif
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
        for (std::int32_t x {}; x < CHUNK_WIDTH; ++x)
        {
            for (std::int32_t y {}; y < CHUNK_HEIGHT; ++y)
            {
                for (std::int32_t z {}; z < CHUNK_LENGTH; ++z)
                {
                    const auto pos {createCubeAt(x + worldCoords.x, y + worldCoords.y, z + worldCoords.z)};
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

    static ChunkData initChunkData(Biome biome, const glm::i32vec3 &position) noexcept
    {
        const auto terrain {WorldGen::generateTerrain(biome)};
        const auto mesh {generateChunkMesh(terrain, position)};
        return {terrain, mesh};
    }


    void init() noexcept 
    {
        createChunksNearPlayer(Camera::getCameraPosChunkOffset());

        finishedInitialization = true;
        while (!stopThread)
            createChunksNearPlayer(Camera::getCameraPosChunkOffset());
    }

    
    /**
     * Returns the specified biome's chunk data
     * (i.e., the mesh and terrain layout).
     */
    ChunkData retrieveChunk(const glm::i32vec3 &position) noexcept
    {
        ChunkData data {std::move(mappedBiomes.at(position))}; // copying the data can be expensive so move it instead
        return data;
    }

    bool hasFinishedStockpiling() noexcept {
        return finishedInitialization;
    }
}