#include "mylib/block/material.hpp"

Material::Material() {}

Material::Material(glm::vec3&& ambientVec, glm::vec3&& specularVec, unsigned int diffuseNum, float shineNum) :
ambient {ambientVec}, specular {specularVec}, diffuse {diffuseNum}, shine {shineNum}
{
}
