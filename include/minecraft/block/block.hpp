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
        Block(BlockName blockName, bool withSFX) noexcept;
        Block(BlockName block, bool withSFX, const glm::vec3 &blockPos) noexcept;
        inline float getTexture() const {return textureCoords[name];}
        inline BlockName getName() const {return name;}
        glm::vec3 position;
    private:
        BlockName name;
};

#endif // BLOCK_HPP
