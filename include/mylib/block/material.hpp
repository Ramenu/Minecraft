#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "glm/glm.hpp"

class Material
{
    public:
        Material();
        Material(const glm::vec3& ambientVec, const glm::vec3& specularVec, uint16_t diffuseNum, float shineNum);
        glm::vec3 ambient;
        glm::vec3 specular;
        unsigned int diffuse;
        float shine;
};

#endif // MATERIAL_HPP
