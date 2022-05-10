#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "minecraft/block/blockenum.hpp"
#include "glm/vec3.hpp"
#include "minecraft/gfx/texture.hpp"
#include <array>


static constexpr std::array textureCoords {[](){
    std::array<float, noBlocks> coords;
    for (uint8_t i {}; i < noBlocks; i++)
        coords[i] = static_cast<float>(i) / atlasHeight;
    return coords;
}()};

class Block
{
    public:
        Block() = default;
        inline constexpr explicit Block(BlockName blockName) noexcept : name {blockName} {}
        inline float getTexture() const noexcept {
            return textureCoords[name - 1]; 
        }
        BlockName name;
};

#endif // BLOCK_HPP
