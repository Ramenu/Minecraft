#ifndef MC_BLOCKENUM_HPP
#define MC_BLOCKENUM_HPP

#include <cstdint>

enum BlockState : std::uint8_t
{
    None = 1,
    Visible = 2,
    Highlighted = 4
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
    Stone_Block
};
static constexpr int NUMBER_OF_BLOCKS {5}; 

#endif // MC_BLOCKENUM_HPP
