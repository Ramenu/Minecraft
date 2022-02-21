#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "mylib/gfx/subtexture.hpp"
#include "mylib/block/blockname.hpp"
#include "mylib/block/material.hpp"

class Block
{
    public:
        Block();
        explicit Block(BlockName block);
        ~Block() = default;
        void drawBlock() const;
        SubTexture blockTexture;
        Material blockMaterial;
};

#endif // BLOCK_HPP