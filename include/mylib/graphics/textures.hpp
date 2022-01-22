#ifndef TEXTURE_HPP
#define TEXTURE_HPP


extern void loadTexture(const char* fileName);
extern void createTexture(const char* filePath, unsigned int& texture);
inline constexpr unsigned int atlasWidth {2}, atlasHeight {2};
inline constexpr float xPos {1.0f / atlasWidth}, yPos {1.0f / atlasHeight};
inline unsigned int textureID {};


#endif
