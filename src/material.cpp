#include "mylib/block/material.hpp"


/* Initializes the material. */
Material::Material(const glm::vec3& materialSpec, uint16_t materialDiff, float materialShine) :
specular {materialSpec},
diffuse {materialDiff},
shine {materialShine} {}
