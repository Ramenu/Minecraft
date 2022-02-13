#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include "mylib/gfx/texture.hpp"
#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#pragma GCC diagnostic ignored "-Wcast-qual"
#pragma GCC diagnostic ignored "-Wuseless-cast"
#include <stb-master/stb_image.h>
#pragma GCC diagnostic pop
#include <iostream>

/* Creates a texture from the filepath given with the default wrapping and filtering configurations. */
void createTexture(const char* filePath, unsigned int& texture)
{
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set the texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    loadTexture(filePath); // Load the texture data 
}

/* Loads the texture from the filename passed. */
void loadTexture(const char* fileName)
{
    using namespace std;
    if (filesystem::exists(fileName))
    {
        int width, height, colourChannels; 
        unsigned char* data = stbi_load(fileName, &width, &height, &colourChannels, 0); // Retrieve image data
        if (filesystem::path(fileName).extension() == ".jpg")
        {
            if (data)
            {
                // Once glTexImage2D is called, the currently bounded texture will have the data attached onto it
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); 
                glGenerateMipmap(GL_TEXTURE_2D); 
            }
            else 
                printf("\nERROR: Failed to load JPG texture \"%s\"\n", fileName);
        }
        else 
        {
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else 
                printf("\nERROR: Failed to load PNG texture \"%s\"\n", fileName);
        }
        stbi_image_free(data);
    }
    else
        printf("\nERROR: No file \"%s\" exists!\n", fileName);
}
