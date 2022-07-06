#define GLM_ENABLE_EXPERIMENTAL // For built-in glm hash

#include "minecraft/world/chunkgenerator.hpp"
#include "minecraft/world/worldgen.hpp"
#if (defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW64__)) && (!defined(__llvm__) && !defined(__INTEL_COMPILER))
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

    bool finishedInitialization {false};
    std::unordered_map<glm::i32vec3, ChunkTerrain> mappedBiomes;



    static inline std::size_t genSuperChunkOffset() noexcept {
        static constexpr int MINIMUM_SUPER_CHUNK_OFFSET {80};
        static constexpr int MAXIMUM_SUPER_CHUNK_OFFSET {800};
        return std::rand() % MAXIMUM_SUPER_CHUNK_OFFSET + MINIMUM_SUPER_CHUNK_OFFSET;
    }

    static inline Biome pickRandomBiome() noexcept {
        static constexpr std::array biomes {
            Plains,
            Forest,
            Desert
        };
        return biomes[std::rand() % biomes.size()];
    }

    /**
     * This function keeps an internal state of
     * 
     */
    static Biome generateBiomeType() noexcept
    {
        static std::size_t maxCalls {genSuperChunkOffset()}; 
        static std::size_t callCount {}; 
        static Biome currentBiome {pickRandomBiome()}; 
        ++callCount;

        // If the number of calls has exceeded the max # of calls, reset the call count and generate a new offset
        // for the super chunk, just to keep things more 'randomized' instead of predictable.
        if (callCount > maxCalls)
        {
            callCount = 0;
            maxCalls = genSuperChunkOffset();
            currentBiome = pickRandomBiome();
        }

        return currentBiome;
    }

    /**
     * Creates chunks near the player's position,
     * where 'p' is the player's chunk offset.
     */
    static void createChunksNearPlayer(const glm::i32vec3 &p) noexcept
    {
        #if 1
        std::int32_t farZ {p.z - RENDER_DISTANCE_Z - PRELOAD_CHUNKS};
        std::int32_t farX {p.x - RENDER_DISTANCE_X - PRELOAD_CHUNKS};
        for (int i {}; i < 2; ++i)
        {
            for (auto x {p.x - RENDER_DISTANCE_X - PRELOAD_CHUNKS}; x < p.x + RENDER_DISTANCE_X + PRELOAD_CHUNKS; ++x)
            {
                const glm::i32vec3 chunkOffset {x, 0, farZ}; 
                if (mappedBiomes.find(chunkOffset) == mappedBiomes.end()) // If not found
                    mappedBiomes.insert({chunkOffset, WorldGen::generateTerrain(generateBiomeType())});
            }
            farZ = p.z + RENDER_DISTANCE_Z + PRELOAD_CHUNKS;
        }

        for (int i {}; i < 2; ++i)
        {
            for (auto z {p.z - RENDER_DISTANCE_Z - PRELOAD_CHUNKS}; z < p.z + RENDER_DISTANCE_Z + PRELOAD_CHUNKS; ++z)
            {
                const glm::i32vec3 chunkOffset {farX, 0, z};
                if (mappedBiomes.find(chunkOffset) == mappedBiomes.end()) 
                    mappedBiomes.insert({chunkOffset, WorldGen::generateTerrain(generateBiomeType())});
            }
            farX = p.x + RENDER_DISTANCE_X + PRELOAD_CHUNKS;
        }
        #else
        for (auto x {p.x - RENDER_DISTANCE_X - PRELOAD_CHUNKS}; x < p.x + RENDER_DISTANCE_X + PRELOAD_CHUNKS; ++x)
        {
            for (auto z {p.z - RENDER_DISTANCE_Z - PRELOAD_CHUNKS}; z < p.z + RENDER_DISTANCE_Z + PRELOAD_CHUNKS; ++z)
            {
                const glm::i32vec3 chunkOffset {x, 0, z};
                if (mappedBiomes.find(chunkOffset) == mappedBiomes.end())
                    mappedBiomes.insert({chunkOffset, initChunkData(generateBiomeType(), chunkOffset)});

            }
        }
        #endif
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
                    const float zW {static_cast<float>(z + worldCoords.z)};
                    auto pos {createCubeAt(xW, yW, zW)};
                    auto blockId {getBlockIDVertices(terrain[x][y][z].name)};
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
        const auto p {Camera::getCameraPosChunkOffset()};
        for (auto x {p.x - RENDER_DISTANCE_X - PRELOAD_CHUNKS}; x < p.x + RENDER_DISTANCE_X + PRELOAD_CHUNKS; ++x)
        {
            for (auto z {p.z - RENDER_DISTANCE_Z - PRELOAD_CHUNKS}; z < p.z + RENDER_DISTANCE_Z + PRELOAD_CHUNKS; ++z)
            {
                const glm::i32vec3 chunkOffset {x, 0, z};
                if (mappedBiomes.find(chunkOffset) == mappedBiomes.end())
                    mappedBiomes.insert({chunkOffset, WorldGen::generateTerrain(generateBiomeType())});

            }
        }
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
        #if 1
        auto chunkTerrain {mappedBiomes.at(position)}; // copying the data can be expensive so move it instead
        auto mesh {generateChunkMesh(chunkTerrain.chunk, position)};
        return {chunkTerrain, mesh};
        #else
            return initChunkData(generateBiomeType(), position);
        #endif
    }

    /**
     * Updates the map to use the given terrain at the key (i.e., position) located.
     * This is useful for when the player makes an update to the chunk, like breaking
     * or placing a block, so that when the chunk is unloaded and loaded back in, the
     * map will retain its state.
     */
    void updateChunkAt(const ChunkTerrain &terrain, const glm::i32vec3 &position) noexcept {
        mappedBiomes[position] = terrain;
    }

    /**
     * Returns true if enough chunks have been
     * stockpiled around the player.
     */
    bool hasFinishedStockpiling() noexcept {
        return finishedInitialization;
    }
}