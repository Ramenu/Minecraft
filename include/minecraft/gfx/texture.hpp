#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "minecraft/block/blockenum.hpp"
#include "minecraft/data/imagedata.h"

namespace Texture
{
    extern void loadTexture(const char *texturePath) noexcept;
    [[nodiscard]] extern ImageData loadImage(const char *imagePath) noexcept;
    extern void createTexture(const char *texturePath, uint32_t &texture) noexcept;
    constexpr uint8_t atlasWidth {3}, atlasHeight {noBlocks - 1};
    constexpr float xPos {1.0f / atlasWidth}, yPos {1.0f / atlasHeight};
    extern uint32_t getTextureAtlas() noexcept;
    extern void initTextureAtlas() noexcept;
    extern void deleteTextureAtlas() noexcept;
}


#endif // TEXTURE_HPP
