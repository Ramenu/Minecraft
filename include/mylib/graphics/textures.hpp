#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GLFW/glfw3.h>

extern void loadTexture(const char* fileName);
extern void createTexture(const char* filePath, GLuint wrap, unsigned int &texture);
extern void setDefaultTextureConfigs();

#endif