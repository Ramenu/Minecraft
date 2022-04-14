#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <cstdint>
#include "minecraft/block/block.hpp"
#include "glm/vec3.hpp"
#include <array>

constexpr uint8_t chunkWidth {16}, chunkHeight {16}, chunkLength {16};
constexpr uint32_t chunkVolume {chunkWidth * chunkHeight * chunkLength};

class Chunk
{
    private:
        static uint32_t chunkIndex;

        /**
         * Initializes the chunk with the the name
         * of the two blocks given. The first parameter
         * specifies the block that will be used to fill
         * the top-most layer, and the second name 
         * is used to fill the bottom layers.
         * The chunk returned is (chunkWidth x ChunkHeight x chunkLength).
         */
        static constexpr std::array<std::array<std::array<Block, chunkWidth>, chunkHeight>, chunkLength> 
        initChunk(BlockName firstLayer, BlockName beneathFirstLayer, BlockName bottomLayer) noexcept
        {
            constexpr uint8_t nearBottomLayer {chunkHeight / 2};
            std::array<std::array<std::array<Block, chunkWidth>, chunkHeight>, chunkLength> blocks;
            for (int8_t x {}; x < chunkWidth; x++)
            {
                BlockName selectedBlock = firstLayer;
                for (int8_t y {chunkHeight - 1}; y >= 0; y--)
                {
                    for (int8_t z {}; z < chunkLength; z++)
                        blocks[x][y][z] = Block{selectedBlock};
                    selectedBlock = (y <= nearBottomLayer) ? bottomLayer : beneathFirstLayer;
                }
            }
            return blocks;
        }
    public:
        const uint32_t index;
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

        Chunk(BlockName firstLayer, BlockName beneathFirstLayer, BlockName bottomLayer) noexcept : 
            index {chunkIndex}, 
            chunk {initChunk(firstLayer, beneathFirstLayer, bottomLayer)}
        {
                chunkIndex++;
        }
};

#endif // CHUNK_HPP
