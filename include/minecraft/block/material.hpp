#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "glm/glm.hpp"

class Material
{
    public:
        Material() = default;
        Material(const glm::vec3 &specular, uint16_t diffuse, float shine);
        glm::vec3 specular {0.8f, 0.8f, 0.8f};
        uint16_t diffuse {0};
        float shine {32.0f};
        float ambient {1.0f};
};

#endif // MATERIAL_HPP
