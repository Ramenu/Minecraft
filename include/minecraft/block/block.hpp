#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "minecraft/block/blockenum.hpp"
#include "glm/vec3.hpp"
#include "minecraft/gfx/texture.hpp"
#include <array>

consteval std::array<float, noBlocks> initTextureCoords()
{
    std::array<float, noBlocks> coords;
    for (uint8_t i {}; i < noBlocks; i++)
        coords[i] = static_cast<float>(i) / Texture::atlasHeight;
    return coords;
}

constexpr std::array<float, noBlocks> textureCoords {initTextureCoords()};

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
