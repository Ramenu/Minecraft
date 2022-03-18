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

    void initTextureAtlas()
    {
        glGenTextures(1, &textureAtlas);
        createTexture("textures/textureatlas.jpg", textureAtlas);
    }

    void deleteTextureAtlas()
    {
        glDeleteTextures(1, &textureAtlas);
    }

    /**
     * Creates a texture from the filepath given with 
     * the default wrapping and filtering configurations. 
     */
    void createTexture(const char *filePath, uint32_t &texture)
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

    /**
     * Loads the texture from the file path given.
     * If unsuccessful, the program will be terminated.
     */
    void loadTexture(const char *texturePath)
    {
        const ImageData img {loadImage(texturePath)};
        if (fs::path(texturePath).extension() == ".jpg")
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.width, img.height, 0, GL_RGB, GL_UNSIGNED_BYTE, img.data); 
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE,img.data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    /** 
     * Returns the data of the image, if successful. Otherwise, will terminate
     * the program. This function has various checks to make sure the path passed
     * is valid (e.g. making sure it exists and making sure it is a supported image format).
     */
    [[nodiscard]] ImageData loadImage(const char *imagePath) 
    {
        if (fs::exists(imagePath))
        {
            const std::string extension {fs::path(imagePath).extension().string()};
            if (extension == ".jpg" || extension == ".png")
            {
                ImageData image {};
                image.data = stbi_load(imagePath, &image.width, &image.height, &image.colorChannels, 0);
                if (image.data != nullptr)
                    return image;
                GLError::error_message("Failed to load data from image");
            }
            GLError::error_message("File format must be .png or .jpg");
        }
        GLError::error_message(std::string{"No file \"" + std::string{imagePath} + "\" could be found. Double check to make sure it exists.\n"}.c_str());
        exit(EXIT_FAILURE); // So the compiler doesn't complain about a return missing
    }
}
