#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "glm/glm.hpp"

class Material
{
    public:
        Material();
        Material(const glm::vec3& ambient, const glm::vec3& specular, uint16_t diffuse, float shine);
        glm::vec3 ambient {};
        glm::vec3 specular {};
        uint16_t diffuse {};
        float shine {};
};

#endif // MATERIAL_HPP
