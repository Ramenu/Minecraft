#ifndef RAY_HPP
#define RAY_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#include "glm/vec3.hpp"
#pragma GCC diagnostic pop
#include "minecraft/debug/debug.hpp"


class Ray
{
    private:
        glm::vec3 ray {};
    public:
        constexpr Ray(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection) noexcept : ray {rayOrigin + rayDirection} {}
        inline void updateRay(const glm::vec3 &origin, const glm::vec3 &direction) noexcept
        {
            // x and y are multiplied by 2 because the width of each block is only 0.5
            // so when the block's x 14, the ray's x will be roughly half of that.
            ray = glm::vec3{origin.x * 2, origin.y - 0.1f, origin.z * 2} + direction;
            setTitle(ray);
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

#endif // RAY_HPP
