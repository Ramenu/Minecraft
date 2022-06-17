#ifndef MC_GLMATH_HPP
#define MC_GLMATH_HPP

#include "glm/vec3.hpp"
#include "minecraft/math/direction.hpp"
#include "minecraft/math/radians.hpp"
#include "minecraft/camera/camera.hpp"
#include "minecraft/window/window.hpp"

namespace GLMath
{
    consteval glm::vec3 get3DUnitVector(Direction direction) noexcept
    {
        switch (direction)
        {
            case Down: return {0.0f, -1.0f, 0.0f};
            case Up: return {0.0f, 1.0f, 0.0f};
            case West: return {-1.0f, 0.0f, 0.0f};
            case East: return {1.0f, 0.0f, 0.0f};
            case South: return {0.0f, 0.0f, -1.0f};
            case North: return {0.0f, 0.0f, 1.0f};
        }
    }
    static constexpr glm::vec3 ZERO_VECTOR_3D {0.0f, 0.0f, 0.0f};
    static constexpr glm::mat4 IDENTITY_MATRIX_4D {glm::mat4{1.0f}};
    static const glm::mat4 PROJECTION {glm::perspective(Camera::FOV.value(), Window::ASPECT_RATIO, Camera::NEAR, Camera::FAR)};
    [[maybe_unused]] static const glm::mat4 INVERSE_PROJECTION {glm::inverse(PROJECTION)};
    extern Direction getDirectionClosestTo(const glm::vec3 &vec) noexcept;

    inline float randf() noexcept {
        return static_cast<float>(std::rand())/static_cast<float>(RAND_MAX);
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    constexpr float smoothstep(T min, T max, T n) noexcept {
        // remove this part if it ends up working.
        if (n <= min)
            return 0.0f;
        if (n >= max)
            return 1.0f;
        n = (n - min) / (max - min);
        return n * n * (3 - 2 * n);
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
