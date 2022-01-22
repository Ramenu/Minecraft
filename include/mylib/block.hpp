#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "mylib/graphics/subtexture.hpp"

class Block
{
    public:
        Block(SubTextures subTexture);
        ~Block();
        void drawBlock() const;
        SubTexture blockTexture;
};

#endif