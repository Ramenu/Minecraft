#ifndef MC_GLMATH_HPP
#define MC_GLMATH_HPP

#include "glm/vec3.hpp"
#include "minecraft/math/direction.hpp"
#include "minecraft/math/radians.hpp"

namespace GLMath
{
    extern Direction getDirectionClosestTo(const glm::vec3 &vec) noexcept;
    inline constexpr double toDegrees(double radians) noexcept {
        return M_PI / 180.0 * radians;
    }

    #if 0
    /**
     * Returns the two missing sides of a
     * right-angle triangle given the angle
     * (in radians) and the hypotenuse.
     */
    inline constexpr glm::vec2 getTriMissingSides_Hyp(Radians radians, float hypotenuse) noexcept {
        return {hypotenuse * std::sin(radians.value()), hypotenuse * cos(radians.value())};
    }

    /**
     * Returns the two missing sides of a
     * right-angle triangle given the angle
     * (in radians) and the adjacent side.
     */
    inline constexpr glm::vec2 getTriMissingSides_Adj(Radians radians, float adjacent) noexcept {
        const float opposite {adjacent * std::tan(radians.value())};
        return {opposite, opposite / std::sin(radians.value())};
    }

    /**
     * Returns the two missing sides of a
     * right-angle triangle given the angle
     * (in radians) and the opposite side.
     */
    inline constexpr glm::vec2 getTriMissingSides_Opp(Radians radians, float opposite) noexcept {
        const float hypotenuse {opposite / std::sin(radians.value())};
        return {hypotenuse, hypotenuse * std::cos(radians.value())};
    }
    #endif
}

#endif // MC_GLMATH_HPP
