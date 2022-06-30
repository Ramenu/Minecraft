#ifndef MC_BLOCKENUM_HPP
#define MC_BLOCKENUM_HPP

#include <cstdint>

enum BlockState : std::uint8_t
{
    None = 0,
    Visible = 1,
    Highlighted = 2,
};

inline constexpr BlockState operator|(BlockState a, BlockState b) noexcept {
    return static_cast<BlockState>(static_cast<uint8_t>(a)|static_cast<uint8_t>(b));
}

inline constexpr BlockState operator&(BlockState a, BlockState b) noexcept {
    return static_cast<BlockState>(static_cast<uint8_t>(a)&static_cast<uint8_t>(b));
}

inline constexpr BlockState &operator|=(BlockState &a, BlockState b) noexcept {
    a = a | b;
    return a;
}

inline constexpr BlockState &operator&=(BlockState &a, BlockState b) noexcept {
    a = a & b;
    return a;
}

enum BlockName : std::uint8_t
{
    Air_Block,
    Grass_Block,
    Cobblestone_Block,
    Dirt_Block,
    Stone_Block,
    CoalOre_Block,
    IronOre_Block,
    GoldOre_Block,
    RedstoneOre_Block,
    DiamondOre_Block,
    EmeraldOre_Block,
    OakWood_Block,
    Leaf_Block,
    Water_Block,
    Sand_Block,
    Cactus_Block
};

static constexpr std::uint8_t NUMBER_OF_BLOCKS {16}; 

#endif // MC_BLOCKENUM_HPP
