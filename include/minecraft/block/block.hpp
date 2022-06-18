#ifndef MC_BLOCK_HPP
#define MC_BLOCK_HPP

#include "minecraft/block/blockenum.hpp"

class Block
{
    public:
        Block() = default;
        inline constexpr explicit Block(BlockName blockName) noexcept : name {blockName} {}
        BlockName name;
};

#endif // MC_BLOCK_HPP
