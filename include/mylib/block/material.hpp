#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <glm/glm.hpp>

class Material
{
    public:
        Material();
        Material(glm::vec3&& ambient, glm::vec3&& specular, const unsigned int diffuse, const float shine);
        glm::vec3 ambient;
        glm::vec3 specular;
        unsigned int diffuse;
        float shine;
};

#endif // MATERIAL_HPP
