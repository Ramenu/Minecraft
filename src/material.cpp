#include "mylib/block/material.hpp"

Material::Material() {}

Material::Material(const glm::vec3& ambientVec, const glm::vec3& specularVec, uint16_t diffuseNum, float shineNum) :
ambient {ambientVec}, specular {specularVec}, diffuse {diffuseNum}, shine {shineNum}
{
}
