#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "minecraft/data/vertexarray.hpp"
#include "minecraft/block/block.hpp"
#include "minecraft/data/vertexbuffer.hpp"
#include "minecraft/data/vertices.hpp"
#include "minecraft/block/face.h"
#include <span>
#include <optional>

static constexpr uint8_t chunkWidth {16}, chunkHeight {16}, chunkLength {16};
static constexpr uint32_t chunkVolume {chunkWidth * chunkHeight * chunkLength};
static_assert(chunkHeight == chunkWidth && chunkHeight == chunkLength, "ERROR: Width, height, and length of the chunk must be equal!");


class Chunk
{
    private:
        GLuint vertexArray;
        GLuint vertexBuffer;
        std::array<float, noOfSquaresInCube> getVisibleFaces(glm::i8vec3 index) const noexcept;
        bool highlightedBlocks[chunkWidth][chunkHeight][chunkLength] {};
        void highlightBlock(glm::i8vec3 index, float ambient) const noexcept;
        std::array<std::optional<glm::i8vec3>, noOfSquaresInCube> getBlocksSurrounding(glm::i8vec3 index) const noexcept;
        void updateChunkVisibility(glm::i8vec3 index) const noexcept;
    public:

        void updateChunkVisibilityToNeighbor(const Chunk &chunkNeighbor, Face face) const noexcept;

        void updateChunkVisibility() const noexcept;

        void initChunk(glm::vec3 position) noexcept;

        void modifyChunk(glm::i8vec3 blockIndex, Block block) noexcept;

        inline void drawChunk() const noexcept
        {
            glBindVertexArray(vertexArray);
            glDrawArrays(GL_TRIANGLES, 0, chunkVolume * attributesToFormCube);
        }

        inline ~Chunk() noexcept
        {
            glDeleteBuffers(1, &vertexBuffer);
            glDeleteVertexArrays(1, &vertexArray);
        }

        void updateChunk(bool &updateNeeded) noexcept;

        void updateBuffer(const ChunkVertex &chunkVertices) const noexcept;

        void updateBuffer(size_t bufferIndex, Attribute attributeIndex, 
                          std::span<const float> vertices, Face face=BackFace) const noexcept;

        bool blockIsVisibleToPlayer(glm::i8vec3 index) const noexcept;
        
        /**
         * This function requires a 3D vector with 3 indices
         * to access the block. Returns true if any of the indices
         * are out of the chunk's array boundaries.
         */
        static inline bool isOutOfChunk(glm::i8vec3 index) noexcept {
            return ((index.x < 0 || index.y < 0 || index.z < 0) ||
                   (index.x >= chunkWidth || index.y >= chunkHeight || index.z >= chunkLength));
        }

        std::array<std::array<std::array<Block, chunkLength>, chunkHeight>, chunkWidth> chunk;

};

#endif // CHUNK_HPP
