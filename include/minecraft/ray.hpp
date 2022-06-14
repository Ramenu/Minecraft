#ifndef MC_RAY_HPP
#define MC_RAY_HPP

#include "glm/vec3.hpp"


class Ray
{
    private:
        glm::vec3 ray {};
    public:
        Ray() = default;
        inline constexpr Ray(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection) noexcept : ray {rayOrigin + rayDirection} {}
        inline void updateRay(const glm::vec3 &origin, const glm::vec3 &direction) noexcept
        {
            ray = origin + direction;
            #if 0
                setTitle({static_cast<int8_t>(ray.x), static_cast<int8_t>(ray.y), static_cast<int8_t>(ray.z)});
            #endif
        }
        inline glm::vec3 getRay() const noexcept {return ray;}
        inline bool intersectsWith(const glm::vec3 &b) const noexcept
        {
            static constexpr float blockWidth {0.5f};
            return (
                (ray.x >= b.x - blockWidth && ray.x < b.x) &&
                (ray.y >= b.y - blockWidth && ray.y < b.y + blockWidth));
        }
};

#endif // MC_RAY_HPP