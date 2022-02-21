#ifndef SUBTEXTURE_HPP
#define SUBTEXTURE_HPP

#include "glm/glm.hpp"
#include "mylib/block/blockname.hpp"

class SubTexture
{
    public:
        SubTexture();
        SubTexture(float column, float row);
        glm::vec2 texCoords;
};

#endif // SUBTEXTURE_HPP
