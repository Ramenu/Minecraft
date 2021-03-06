#ifndef MC_CHUNK_HPP
#define MC_CHUNK_HPP

#include "minecraft/data/vertexarray.hpp"
#include "minecraft/block/block.hpp"
#include "minecraft/data/vertexbuffer.hpp"
#include "minecraft/mesh/chunkmesh.hpp"
#include "minecraft/block/face.h"
#include "minecraft/math/shape/sphere.hpp"
#include "minecraft/world/biome.h"
#include "glm/vec3.hpp"
#include <span>
#include <optional>

static constexpr std::int32_t CHUNK_WIDTH {16}, CHUNK_HEIGHT {CHUNK_WIDTH}, CHUNK_LENGTH {CHUNK_WIDTH};
static constexpr float CHUNK_WIDTH_F {static_cast<float>(CHUNK_WIDTH)}, 
                       CHUNK_HEIGHT_F {static_cast<float>(CHUNK_HEIGHT)}, 
                       CHUNK_LENGTH_F {static_cast<float>(CHUNK_LENGTH)};
static constexpr std::int32_t CHUNK_HEIGHT_HALF {CHUNK_HEIGHT / 2};
static constexpr std::size_t CHUNK_VOLUME {CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LENGTH};
static constexpr float CHUNK_RADIUS {60.0f};
static constexpr glm::vec3 CHUNK_OFFSET {CHUNK_WIDTH, CHUNK_HEIGHT, CHUNK_LENGTH};
static constexpr glm::vec3 CHUNK_CENTER {CHUNK_WIDTH / 2.0f, CHUNK_HEIGHT / 2.0f, CHUNK_LENGTH / 2.0f};
static_assert(CHUNK_HEIGHT == CHUNK_WIDTH && CHUNK_HEIGHT == CHUNK_LENGTH, "ERROR: Width, height, and length of the chunk must be equal!");

using ChunkArray = std::array<std::array<std::array<Block, CHUNK_LENGTH>, CHUNK_HEIGHT>, CHUNK_WIDTH>;

struct ChunkTerrain
{
    ChunkArray chunk;
    std::uint8_t topLayer {CHUNK_HEIGHT - 1};
    std::uint8_t lowestLayer {CHUNK_HEIGHT_HALF};
};

struct ChunkData
{
    ChunkTerrain terrain;
    ChunkMesh mesh;
};

class Chunk
{
    private:
        GLuint vertexArray;
        GLuint vertexBuffer;
        std::uint8_t lowestVisibleLayer {CHUNK_HEIGHT_HALF}; // Minimum visible height level for a chunk
        std::uint8_t highestVisibleLayer {CHUNK_HEIGHT}; // Maximum visible height level for a chunk
        constexpr std::array<float, SQUARES_ON_CUBE> getVisibleFaces(glm::i8vec3 index) const noexcept;
        BlockState blockStates[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_LENGTH] {};
        void highlightBlock(glm::i8vec3 index, float ambient) const noexcept;
        static std::array<std::optional<glm::i8vec3>, SQUARES_ON_CUBE> getBlocksSurrounding(glm::i8vec3 index) noexcept;
        void updateChunkVisibility(glm::i8vec3 index) noexcept;
        static void updateBuffer(size_t bufferIndex, Attribute attributeIndex, 
                                 std::span<const float> vertices, Face face=BackFace) noexcept;
        ChunkArray chunk;
    public:

        inline constexpr auto getTopLayer() const noexcept {return highestVisibleLayer;}

        inline constexpr auto getBottomLayer() const noexcept {return lowestVisibleLayer;}

        inline const constexpr auto &getChunk() const noexcept {return chunk;}
        
        void updateChunkVisibilityToNeighbor(const ChunkArray &chunkNeighbor, Face face) const noexcept;

        void updateChunkVisibility() noexcept;

        void initChunk(glm::vec3 position) noexcept;

        inline ~Chunk() noexcept {
            glDeleteBuffers(1, &vertexBuffer);
            glDeleteVertexArrays(1, &vertexArray);
        }

        void modifyChunk(glm::i8vec3 blockIndex, Block block) noexcept;

        void drawChunk() const noexcept;

        bool updateChunk() noexcept;

        constexpr bool blockIsVisibleToPlayer(glm::i8vec3 index) const noexcept;
        
        /**
         * This function requires a 3D vector with 3 indices
         * to access the block. Returns true if any of the indices
         * are out of the chunk's array boundaries.
         */
        template<typename T>
        static inline constexpr bool isOutOfChunk(const T &index) noexcept {
            return ((index.x < 0 || index.y < 0 || index.z < 0) ||
                   (index.x >= CHUNK_WIDTH || index.y >= CHUNK_HEIGHT || index.z >= CHUNK_LENGTH));
        }

        static inline constexpr glm::vec3 getChunkGlobalOffset(const glm::vec3 &chunkPos) noexcept {
            return chunkPos * CHUNK_OFFSET;
        }

        static inline constexpr Sphere getChunkBoundingSphere(const glm::vec3 &chunkPos) noexcept {
            return {getChunkGlobalOffset(chunkPos), CHUNK_RADIUS};
        }

        static bool isFacingChunk(const glm::vec3 &chunkWorldPos) noexcept;

        constexpr bool faceIsVisible(glm::i8vec3 index) const noexcept;
        

};

#endif // MC_CHUNK_HPP
