#ifndef BLOCKENUM_HPP
#define BLOCKENUM_HPP

#include <cstdint>

enum class BlockState : uint8_t
{
    None,
    Highlighted
};

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
