#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <cstdint>
#include "minecraft/block/block.hpp"
#include "glm/vec3.hpp"
#include <array>
#include "minecraft/data/vertices.hpp"

constexpr uint8_t chunkWidth {16}, chunkHeight {16}, chunkLength {16};
constexpr uint32_t chunkVolume {chunkWidth * chunkHeight * chunkLength};

class Chunk
{
    private:
        ChunkVertex chunkVertices;
        void updateChunkVisibility() noexcept;
    public:
        Chunk(BlockName firstLayer, BlockName bottomLayers) noexcept;
        void modifyChunk(uint8_t x, uint8_t y, uint8_t z,
                         Block block,
                         const std::array<float, noOfSquaresInCube> &visible) noexcept;
        inline ChunkVertex getVertices() const {return chunkVertices;}
        bool blockIsVisibleToPlayer(const glm::vec3 &block3DIndex) const noexcept;
        /**
         * This function requires a 3D vector with 3 indices
         * to access the block. Returns true if any of the indices
         * are out of the chunk's array boundaries.
         */
        static inline bool isOutOfChunk(const glm::vec3 &pos) {
            return ((pos.x < 0.0f || pos.y < 0.0f || pos.z < 0.0f) ||
                   (pos.x >= chunkWidth || pos.y >= chunkHeight || pos.z >= chunkLength));
        }

        std::array<std::array<std::array<Block, chunkLength>, chunkHeight>, chunkWidth> chunk;
        

};

#endif // CHUNK_HPP
