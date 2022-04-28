#ifndef GLMATH_HPP
#define GLMATH_HPP

#include "glm/vec3.hpp"
#include "minecraft/math/direction.hpp"

namespace GLMath
{
    extern Direction getDirectionClosestTo(const glm::vec3 &vec) noexcept;
}

#endif // GLMATH_HPP
