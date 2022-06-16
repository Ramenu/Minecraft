#ifndef MC_WORLDGEN_HPP
#define MC_WORLDGEN_HPP

#include "minecraft/rendering/chunk.hpp"

namespace WorldGen
{
    enum Biome : std::uint8_t
    {
        Plains
    };

    extern std::array<std::array<std::array<Block, CHUNK_WIDTH>, CHUNK_HEIGHT>, CHUNK_LENGTH> generateTerrain(Biome biome) noexcept;
    extern void initSeed() noexcept;
}

#endif // MC_WORLDGEN_HPP
