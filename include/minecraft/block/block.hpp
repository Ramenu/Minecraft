#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "minecraft/block/blockenum.hpp"
#include "glm/vec3.hpp"
#include "minecraft/gfx/texture.hpp"

constexpr float textureCoords[noBlocks] = {
    0.0f,
    1.0f / Texture::atlasHeight,
    2.0f / Texture::atlasHeight
};

class Block
{
    public:
        Block() = default;
        constexpr Block(BlockName blockName) : name {blockName} {}
        inline float getTexture() const {
            return textureCoords[name - 1]; 
        }
        BlockName name;
};

#endif // BLOCK_HPP
