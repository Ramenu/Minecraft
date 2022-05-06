#define STB_IMAGE_IMPLEMENTATION
#include "glad/glad.h"
#include <filesystem>
#include "minecraft/gfx/texture.hpp"
#if defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW64__)
    #pragma GCC diagnostic push 
    #pragma GCC diagnostic ignored "-Wdouble-promotion"
    #pragma GCC diagnostic ignored "-Wcast-qual"
    #pragma GCC diagnostic ignored "-Wuseless-cast"
    #pragma GCC diagnostic ignored "-Wduplicated-branches"
    #pragma GCC diagnostic ignored "-Wconversion"
    #include "stb-master/stb_image.h"
#pragma GCC diagnostic pop
#else
    #include "stb-master/stb_image.h"
#endif
#include "minecraft/glerror/glerror.hpp"

namespace std_fs = std::filesystem;


/**
 * Creates a texture from the filepath given with 
 * the default wrapping and filtering configurations. 
 */
Texture::Texture(const std::string &pathToTexture) noexcept
{
    if (std_fs::exists(pathToTexture))
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Set the texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int width, height, colorChannels;
        unsigned char *data {stbi_load(pathToTexture.c_str(), &width, &height, &colorChannels, 0)};

        if (data)
        {
            static constexpr int mipmapLevel {0};
            const auto format {(pathToTexture == ".png") ? GL_RGBA : GL_RGB};
            glTexImage2D(GL_TEXTURE_2D, mipmapLevel, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(data);
            return;
        }
        GLError::error_message("Failed to load data from \"" + pathToTexture + '\"');
    }
    GLError::error_message("File \"" + pathToTexture + "\" could not be found");
}

Texture::~Texture() noexcept
{
    glDeleteTextures(1, &texture);
}
