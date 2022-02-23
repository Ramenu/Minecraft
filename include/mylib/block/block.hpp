#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "mylib/gfx/subtexture.hpp"
#include "mylib/block/blockname.hpp"
#include "mylib/block/material.hpp"

class Block
{
    public:
        explicit Block(BlockName block);
        ~Block() = default;
        SubTexture blockTexture;
        Material blockMaterial;
};

#endif // BLOCK_HPP