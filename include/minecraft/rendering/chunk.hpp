#ifndef MC_CHUNK_HPP
#define MC_CHUNK_HPP

#include "minecraft/data/vertexarray.hpp"
#include "minecraft/block/block.hpp"
#include "minecraft/data/vertexbuffer.hpp"
#include "minecraft/mesh/chunkmesh.hpp"
#include "minecraft/block/face.h"
#include "glm/vec3.hpp"
#include <span>
#include <optional>

static constexpr std::int32_t CHUNK_WIDTH {16}, CHUNK_HEIGHT {CHUNK_WIDTH}, CHUNK_LENGTH {CHUNK_WIDTH};
static constexpr std::size_t CHUNK_VOLUME {CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LENGTH};
static_assert(CHUNK_HEIGHT == CHUNK_WIDTH && CHUNK_HEIGHT == CHUNK_LENGTH, "ERROR: Width, height, and length of the chunk must be equal!");


class Chunk
{
    private:
        GLuint vertexArray;
        GLuint vertexBuffer;
        constexpr std::array<float, SQUARES_ON_CUBE> getVisibleFaces(glm::i8vec3 index) const noexcept;
        BlockState blockStates[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_LENGTH] {};
        void highlightBlock(glm::i8vec3 index, float ambient) const noexcept;
        static std::array<std::optional<glm::i8vec3>, SQUARES_ON_CUBE> getBlocksSurrounding(glm::i8vec3 index) noexcept;
        void updateChunkVisibility(glm::i8vec3 index) noexcept;
        static void updateBuffer(size_t bufferIndex, Attribute attributeIndex, 
                                 std::span<const float> vertices, Face face=BackFace) noexcept;
        std::array<std::array<std::array<Block, CHUNK_LENGTH>, CHUNK_HEIGHT>, CHUNK_WIDTH> chunk;
    public:

        inline constexpr auto getChunk() const noexcept {return chunk;}
        
        void updateChunkVisibilityToNeighbor(const std::array<std::array<std::array<Block, CHUNK_LENGTH>, CHUNK_HEIGHT>, CHUNK_WIDTH> &chunkNeighbor,
                                             Face face) const noexcept;

        void updateChunkVisibility() noexcept;

        void initChunk(glm::vec3 position) noexcept;

        inline ~Chunk() noexcept {
            glDeleteBuffers(1, &vertexBuffer);
            glDeleteVertexArrays(1, &vertexArray);
        }

        void modifyChunk(glm::i8vec3 blockIndex, Block block) noexcept;

        void drawChunk() const noexcept;

        void deleteChunk() noexcept;

        bool updateChunk() noexcept;

        bool blockIsVisibleToPlayer(glm::i8vec3 index) const noexcept;
        
        /**
         * This function requires a 3D vector with 3 indices
         * to access the block. Returns true if any of the indices
         * are out of the chunk's array boundaries.
         */
        static inline constexpr bool isOutOfChunk(glm::i8vec3 index) noexcept {
            return ((index.x < 0 || index.y < 0 || index.z < 0) ||
                   (index.x >= CHUNK_WIDTH || index.y >= CHUNK_HEIGHT || index.z >= CHUNK_LENGTH));
        }

        static inline constexpr bool isOutOfChunk(const glm::i32vec3 &index) noexcept {
            return ((index.x < 0 || index.y < 0 || index.z < 0) ||
                   (index.x >= CHUNK_WIDTH || index.y >= CHUNK_HEIGHT || index.z >= CHUNK_LENGTH));
        }

        constexpr bool faceIsVisible(glm::i8vec3 index) const noexcept;
        

};

#endif // MC_CHUNK_HPP
