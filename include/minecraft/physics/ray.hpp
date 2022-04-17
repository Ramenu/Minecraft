#ifndef RAY_HPP
#define RAY_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#include "glm/vec3.hpp"
#pragma GCC diagnostic pop


class Ray
{
    public:
        constexpr Ray(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection) noexcept : ray {rayOrigin + rayDirection} {}
        inline void updateRay(const glm::vec3 &origin, const glm::vec3 &direction) noexcept
        {
            ray = glm::vec3{origin.x, origin.y - 0.1f, origin.z} + direction;
        }
        inline glm::vec3 getRay() const noexcept {return ray;}
        inline bool intersectsWith(const glm::vec3 &b) const noexcept
        {
            constexpr float blockWidth {0.5f};
            return (
                (ray.x >= b.x - blockWidth && ray.x < b.x) &&
                (ray.y >= b.y - blockWidth && ray.y < b.y + blockWidth));
        }
    private:
        glm::vec3 ray {};
};

#endif // RAY_HPP
