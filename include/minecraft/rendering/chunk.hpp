#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <cstdint>
#include "minecraft/block/block.hpp"
#include "glm/vec3.hpp"
#include <array>
#include "minecraft/data/vertices.hpp"

constexpr uint8_t chunkWidth {16}, chunkHeight {16}, chunkLength {16};
constexpr size_t chunkVolume {chunkWidth * chunkHeight * chunkLength};

class Chunk
{
    private:
        ChunkVertex chunkVertices;
    public:
        Chunk() noexcept;
        void modifyChunk(uint8_t x, uint8_t y, uint8_t z,
                         Block block,
                         const std::array<float, noOfSquaresInCube> &visible) noexcept;
        inline ChunkVertex getVertices() const {return chunkVertices;}
        

};

#endif // CHUNK_HPP
