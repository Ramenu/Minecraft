#ifndef SUBTEXTURE_HPP
#define SUBTEXTURE_HPP

#include <glm/glm.hpp>

enum class SubTextures
{
    GRASS_BLOCK,
    COBBLESTONE_BLOCK
};

class SubTexture
{
    public:
        SubTexture();
        SubTexture(const float& column, const float& row);
        ~SubTexture();
        glm::vec2 texCoords;
};

#endif
