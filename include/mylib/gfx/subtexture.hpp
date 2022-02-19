#ifndef SUBTEXTURE_HPP
#define SUBTEXTURE_HPP

#include <glm/glm.hpp>
#include "mylib/block/blockname.hpp"

class SubTexture
{
    public:
        explicit SubTexture();
        explicit SubTexture(float column, float row);
        ~SubTexture();
        glm::vec2 texCoords;
};

#endif // SUBTEXTURE_HPP
