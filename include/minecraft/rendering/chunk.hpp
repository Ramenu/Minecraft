#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <cstdint>
#include "minecraft/block/block.hpp"
#include "glm/vec3.hpp"
#include <array>

constexpr uint8_t chunkWidth {5}, chunkHeight {5}, chunkLength {5};

class Chunk
{
    private:
        /**
         * Initializes the chunk with the the name
         * of the two blocks given. The first parameter
         * specifies the block that will be used to fill
         * the top-most layer, and the second name 
         * is used to fill the bottom layers.
         * The chunk returned is (chunkWidth x ChunkHeight x chunkLength).
         */
        static constexpr std::array<std::array<std::array<Block, chunkWidth>, chunkHeight>, chunkLength> 
        initChunk(BlockName firstLayer, BlockName beneathFirstLayer) noexcept
        {
            std::array<std::array<std::array<Block, chunkWidth>, chunkHeight>, chunkLength> blocks;
            for (int8_t i {}; i < chunkWidth; i++)
            {
                BlockName selectedBlock = firstLayer;
                for (int8_t j {chunkHeight - 1}; j >= 0; j--)
                {
                    for (int8_t k {}; k < chunkLength; k++)
                        blocks[i][j][k] = Block{selectedBlock};
                    selectedBlock = beneathFirstLayer;
                }
            }
            return blocks;
        }
    public:
        /**
         * Returns true if the position/indices 
         * is out of the chunk array's boundaries.
         */
        static inline bool isOutOfChunk(const glm::vec3 &pos) {
            return ((pos.x >= chunkWidth || pos.y >= chunkHeight || pos.z >= chunkLength) || 
                   (pos.x < 0.0f || pos.y < 0.0f || pos.z < 0.0f));
        }
        std::array<std::array<std::array<Block, chunkWidth>, chunkHeight>, chunkLength> chunk;
        bool blockIsVisibleToPlayer(const glm::vec3 &blockIndex) const noexcept;
        constexpr Chunk(BlockName firstLayer, BlockName beneathFirstLayer) : chunk {initChunk(firstLayer, beneathFirstLayer)} {}
};


#endif // CHUNK_HPP
