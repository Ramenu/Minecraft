#ifndef GLMATH_HPP
#define GLMATH_HPP

#include "glm/vec3.hpp"

namespace GLMath
{
    extern glm::vec3 getNearest3DDirectionTo(const glm::vec3 &vec) noexcept;
    extern glm::vec3 getDirectionOfYaw(float yaw) noexcept;
}

#endif // GLMATH_HPP
