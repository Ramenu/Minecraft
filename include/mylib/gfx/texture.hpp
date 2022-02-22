#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <cstdint>
#include "mylib/imagedata.h"

namespace Texture
{
    extern void loadTexture(const char* fileName);
    [[nodiscard]] extern ImageData loadImage(const char* fileName);
    extern void createTexture(const char* filePath, uint32_t& texture);
    constexpr uint16_t atlasWidth {2}, atlasHeight {2};
    constexpr float xPos {1.0f / atlasWidth}, yPos {1.0f / atlasHeight};
    extern unsigned int getTextureAtlas();
    extern void initTextureAtlas();
    extern void deleteTextureAtlas();
}


#endif // TEXTURE_HPP
