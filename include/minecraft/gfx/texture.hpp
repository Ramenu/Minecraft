#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <cstdint>
#include "minecraft/data/imagedata.h"

namespace Texture
{
    extern void loadTexture(const char *texturePath);
    [[nodiscard]] extern ImageData loadImage(const char *imagePath);
    extern void createTexture(const char *texturePath, uint32_t &texture);
    constexpr uint16_t atlasWidth {3}, atlasHeight {2};
    constexpr float xPos {1.0f / atlasWidth}, yPos {1.0f / atlasHeight};
    extern uint32_t getTextureAtlas();
    extern void initTextureAtlas();
    extern void deleteTextureAtlas();
}


#endif // TEXTURE_HPP
