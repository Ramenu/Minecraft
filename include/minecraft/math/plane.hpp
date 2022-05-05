#ifndef PLANE_HPP
#define PLANE_HPP

#include "glm/vec3.hpp"

struct Plane
{
    glm::vec3 normal {0.0f, 1.0f, 0.0f};
    float distance {0.0f};
};

#endif // PLANE_HPP
