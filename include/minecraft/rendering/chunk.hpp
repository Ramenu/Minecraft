#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "minecraft/data/vertexarray.hpp"
#include "minecraft/block/block.hpp"
#include "minecraft/data/vertexbuffer.hpp"
#include "minecraft/mesh/chunkmesh.hpp"
#include "minecraft/block/face.h"
#include <span>
#include <optional>

static constexpr std::int32_t chunkWidth {16}, chunkHeight {chunkWidth}, chunkLength {chunkWidth};
static constexpr std::size_t chunkVolume {chunkWidth * chunkHeight * chunkLength};
static_assert(chunkHeight == chunkWidth && chunkHeight == chunkLength, "ERROR: Width, height, and length of the chunk must be equal!");


class Chunk
{
    private:
        GLuint vertexArray;
        GLuint vertexBuffer;
        std::array<float, noOfSquaresInCube> getVisibleFaces(glm::i8vec3 index) const noexcept;
        BlockState blockStates[chunkWidth][chunkHeight][chunkLength] {};
        void highlightBlock(glm::i8vec3 index, float ambient) const noexcept;
        static std::array<std::optional<glm::i8vec3>, noOfSquaresInCube> getBlocksSurrounding(glm::i8vec3 index) noexcept;
        void updateChunkVisibility(glm::i8vec3 index) noexcept;
        static void updateBuffer(size_t bufferIndex, Attribute attributeIndex, 
                                 std::span<const float> vertices, Face face=BackFace) noexcept;
        static bool anyFacesAreVisible(const std::array<float, noOfSquaresInCube> &faces);
        std::array<std::array<std::array<Block, chunkLength>, chunkHeight>, chunkWidth> chunk;
    public:

        inline auto getChunk() const noexcept {return chunk;}
        
        void updateChunkVisibilityToNeighbor(const std::array<std::array<std::array<Block, chunkLength>, chunkHeight>, chunkWidth> &chunkNeighbor,
                                             Face face) const noexcept;

        void updateChunkVisibility() noexcept;

        void initChunk(glm::vec3 position) noexcept;

        void modifyChunk(glm::i8vec3 blockIndex, Block block) noexcept;

        void drawChunk() const noexcept;

        inline ~Chunk() noexcept
        {
            glDeleteBuffers(1, &vertexBuffer);
            glDeleteVertexArrays(1, &vertexArray);
        }

        bool updateChunk() noexcept;

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


};

#endif // CHUNK_HPP
