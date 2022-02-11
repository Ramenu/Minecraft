#include "mylib/block/material.hpp"

Material::Material() {}

Material::Material(glm::vec3&& ambient, glm::vec3&& specular, const unsigned int diffuse, const float shine) :
ambient {ambient}, specular {specular}, diffuse {diffuse}, shine {shine}
{
}
