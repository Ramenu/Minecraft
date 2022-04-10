#ifndef GLMATH_HPP
#define GLMATH_HPP

#include "glm/vec3.hpp"

namespace GLMath
{
    extern glm::vec3 closestDirectionTo(const glm::vec3 &vec) noexcept;

    /**
     * Returns the position of the block
     * based on (x, y, z) coordinates passed.
     */
    inline glm::vec3 getBlockPos(const glm::vec3 &location) {
        return glm::vec3{0.5f * location.x, location.y, location.z * 0.5f};
    }
}

#endif // GLMATH_HPP
