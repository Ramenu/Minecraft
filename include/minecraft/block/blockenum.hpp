#ifndef BLOCKENUM_HPP
#define BLOCKENUM_HPP

#include <cstdint>

enum BlockName : uint8_t
{
    Grass_Block,
    Cobblestone_Block,
    Dirt_Block
};
constexpr uint8_t noBlocks {3}; 

#endif // BLOCKENUM_HPP
