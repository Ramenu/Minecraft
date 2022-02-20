#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <cstdint>
#include "mylib/imagedata.h"

extern void loadTexture(const char* fileName);
extern void loadImage(const char* fileName, ImageData& image);
extern void createTexture(const char* filePath, uint32_t& texture);
inline constexpr uint16_t atlasWidth {2}, atlasHeight {2};
inline constexpr float xPos {1.0f / atlasWidth}, yPos {1.0f / atlasHeight};
inline uint32_t textureID {};


#endif // TEXTURE_HPP
