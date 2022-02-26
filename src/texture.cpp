#define STB_IMAGE_IMPLEMENTATION
#include "glad/glad.h"
#include <filesystem>
#include "minecraft/gfx/texture.hpp"
#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#pragma GCC diagnostic ignored "-Wcast-qual"
#pragma GCC diagnostic ignored "-Wuseless-cast"
#include <stb-master/stb_image.h>
#pragma GCC diagnostic pop
#include "minecraft/glerror.hpp"

namespace fs = std::filesystem;

namespace Texture
{
    static uint32_t textureAtlas;

    uint32_t getTextureAtlas() {return textureAtlas;}

    /* Initializes the texture atlas, should be called when the game starts. */
    void initTextureAtlas()
    {
        glGenTextures(1, &textureAtlas);
        createTexture("textures/textureatlas.jpg", textureAtlas);
    }

    /* Deletes the texture atlas, should be called when the game is terminated. */
    void deleteTextureAtlas()
    {
        glDeleteTextures(1, &textureAtlas);
    }

    /* Creates a texture from the filepath given with the default wrapping and filtering configurations. */
    void createTexture(const char* filePath, uint32_t& texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture);

        // Set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Set the texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        loadTexture(filePath); 
    }

    /* Loads the texture from the filename passed. */
    void loadTexture(const char* fileName)
    {
        const ImageData img {loadImage(fileName)};
        if (img.data)
        {
            if (fs::path(fileName).extension() == ".jpg")
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.width, img.height, 0, GL_RGB, GL_UNSIGNED_BYTE, img.data); 
            else
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE,img.data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
            GLError::error_message(std::string{"Failed to load image data from \"" + std::string{fileName} + '\"'}.c_str());
    }

    /* Returns a pointer to the image loaded, if successful, otherwise will return a nullptr. */
    [[nodiscard]] ImageData loadImage(const char* fileName) 
    {
        if (fs::exists(fileName))
        {
            if (fs::path(fileName).extension() == ".jpg" || fs::path(fileName).extension() == ".png")
            {
                ImageData image;
                image.data = stbi_load(fileName, &image.width, &image.height, &image.colorChannels, 0);
                return image;
            }
            else
                GLError::error_message("File format must be .png or .jpg");
        }
        else
            GLError::error_message(std::string{"No file \"" + std::string{fileName} + "\" could be found. Double check to make sure it exists.\n"}.c_str());
        throw; // Impossible to reach here, but put a throw here anyway just so the compiler does not complain about a return missing
    }
}
