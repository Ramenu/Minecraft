#ifndef TEXTURES_H
#define TEXTURES_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb-master/stb_image.h>
#include <iostream>

class Textures {
    public:
        void loadTexture(const char* fileName, bool isJPG);
        void set_Default_2D_Texture_Configs();

};

#endif