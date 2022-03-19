#ifndef RAY_HPP
#define RAY_HPP

#include "minecraft/shader.hpp"
#include "minecraft/buffer.hpp"

class Ray
{
    public:
        inline Ray(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection) noexcept :
            origin {rayOrigin},
            direction {rayDirection} {}
        inline void updateRay() noexcept {ray = glm::vec3{origin.x, origin.y - 0.1f, origin.z} + direction;}
        inline glm::vec3 getRay() const noexcept {return ray;}
        glm::vec3 origin;
        glm::vec3 direction;
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
