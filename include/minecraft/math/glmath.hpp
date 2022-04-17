#ifndef GLMATH_HPP
#define GLMATH_HPP

#include "glm/vec3.hpp"

namespace GLMath
{
    extern glm::vec3 closestDirectionTo(const glm::vec3 &vec) noexcept;
    extern glm::vec3 nearestBlockTo(const glm::vec3 &vec) noexcept;
}

#endif // GLMATH_HPP
