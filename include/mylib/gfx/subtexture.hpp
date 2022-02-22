#ifndef SUBTEXTURE_HPP
#define SUBTEXTURE_HPP

#include "glm/vec2.hpp"

class SubTexture
{
    public:
        SubTexture();
        SubTexture(float column, float row);
        glm::vec2 texCoords;

};

#endif // SUBTEXTURE_HPP
