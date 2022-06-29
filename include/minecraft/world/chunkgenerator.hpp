#ifndef MC_CHUNKGENERATOR_HPP
#define MC_CHUNKGENERATOR_HPP

#include "minecraft/world/biome.h"
#include "minecraft/mesh/chunkmesh.hpp"
#include "minecraft/rendering/chunk.hpp"


namespace ChunkGenerator
{
    inline bool stopThread {false};
    extern void init() noexcept;
    extern ChunkData retrieveChunk(const glm::i32vec3 &position) noexcept;
    extern bool hasFinishedStockpiling() noexcept;
}

#endif // MC_CHUNKGENERATOR_HPP