#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <cstdint>
#include "minecraft/block/block.hpp"
#include "glm/vec3.hpp"
#include <array>
#include "minecraft/data/vertices.hpp"

constexpr uint8_t chunkWidth {16}, chunkHeight {16}, chunkLength {16};
constexpr uint32_t chunkVolume {chunkWidth * chunkHeight * chunkLength};

struct ChunkIndex
{
    int8_t x;
    int8_t y;
    int8_t z;
    ChunkIndex operator+(int8_t num)
    {
        const int8_t newX = x + num,
                     newY = y + num,
                     newZ = z + num;
        return ChunkIndex{newX, newY, newZ};
    }
    ChunkIndex operator-(int8_t num)
    {
        const int8_t newX = x - num,
                     newY = y - num,
                     newZ = z - num;
        return ChunkIndex{newX, newY, newZ};
    }
};

class Chunk
{
    private:
        ChunkVertex chunkVertices;
        std::array<float, noOfSquaresInCube> getVisibleFaces(ChunkIndex index) const noexcept;
    public:
        void updateChunkVisibility() noexcept;
        Chunk(BlockName firstLayer, BlockName bottomLayers) noexcept;
        void modifyChunk(ChunkIndex chunkIndex, Block block) noexcept;
        inline ChunkVertex getVertices() const {return chunkVertices;}
        bool blockIsVisibleToPlayer(ChunkIndex index) const noexcept;
        /**
         * This function requires a 3D vector with 3 indices
         * to access the block. Returns true if any of the indices
         * are out of the chunk's array boundaries.
         */
        static inline bool isOutOfChunk(ChunkIndex index) noexcept {
            return ((index.x < 0 || index.y < 0 || index.z < 0) ||
                   (index.x >= chunkWidth || index.y >= chunkHeight || index.z >= chunkLength));
        }

        std::array<std::array<std::array<Block, chunkLength>, chunkHeight>, chunkWidth> chunk;
        

};

#endif // CHUNK_HPP
