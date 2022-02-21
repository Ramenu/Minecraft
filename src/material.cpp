#include "mylib/block/material.hpp"

Material::Material() {}

/* Initializes the material. */
Material::Material(const glm::vec3& materialAmb, const glm::vec3& materialSpec, uint16_t materialDiff, float materialShine) :
ambient {materialAmb},
specular {materialSpec},
diffuse {materialDiff},
shine {materialShine} {}
