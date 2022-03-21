#ifndef BLOCKENUM_HPP
#define BLOCKENUM_HPP

#include <cstdint>

enum class BlockName
{
    Grass_Block,
    Cobblestone_Block
};

enum BlockSoundID : uint8_t
{
    Grass_Block = 0,
    Stone_Block = 1
};

#endif // BLOCKENUM_HPP
