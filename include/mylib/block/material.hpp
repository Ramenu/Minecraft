#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <glm/glm.hpp>

class Material
{
    public:
        Material();
        Material(glm::vec3&& ambientVec, glm::vec3&& specularVec, const unsigned int diffuseNum, const float shineNum);
        glm::vec3 ambient;
        glm::vec3 specular;
        unsigned int diffuse;
        float shine;
};

#endif // MATERIAL_HPP
