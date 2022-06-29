#ifndef MC_WORLDGEN_HPP
#define MC_WORLDGEN_HPP

#include "minecraft/rendering/chunk.hpp"
#include "minecraft/world/biome.h"

namespace WorldGen
{
    extern std::pair<ChunkArray, std::uint8_t> generateTerrain(Biome biome) noexcept;
    extern void initSeed() noexcept;
}

#endif // MC_WORLDGEN_HPP
