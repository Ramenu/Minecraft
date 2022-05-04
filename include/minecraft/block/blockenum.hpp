#ifndef BLOCKENUM_HPP
#define BLOCKENUM_HPP

#include <cstdint>

enum BlockState : uint8_t
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

enum BlockName : uint8_t
{
    Air_Block,
    Grass_Block,
    Cobblestone_Block,
    Dirt_Block,
    Stone_Block
};
static constexpr uint8_t noBlocks {5}; 

#endif // BLOCKENUM_HPP
