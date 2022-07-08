#ifndef MC_RAY_HPP
#define MC_RAY_HPP

#include "glm/vec3.hpp"
#include "minecraft/debug/debug.hpp"


class Ray
{
    private:
        glm::vec3 ray {};
    public:
        Ray() = default;
        inline constexpr Ray(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection) noexcept : ray {rayOrigin + rayDirection} {}
        inline constexpr void updateRay(const glm::vec3 &origin, const glm::vec3 &direction) noexcept
        {
			const float distance {2.0F};
            ray = origin + direction * distance;
            #if 0
                //setTitle({static_cast<int8_t>(ray.x), static_cast<int8_t>(ray.y), static_cast<int8_t>(ray.z)});
                setTitle(ray);
            #endif
        }
        inline glm::vec3 getRay() const noexcept {return ray;}
};

#endif // MC_RAY_HPP
