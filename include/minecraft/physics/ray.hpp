#ifndef RAY_HPP
#define RAY_HPP

#include "minecraft/shader.hpp"
#include "minecraft/buffer.hpp"

struct Line
{
    glm::vec3 origin;
    glm::vec3 direction;
};

class Ray
{
    public:
        inline explicit Ray(const Line &line) : ray {line.origin + line.direction} {}
        inline void updateRay(const Line &line) noexcept {ray = glm::vec3{line.origin.x, line.origin.y - 0.1f, line.origin.z} + line.direction;}
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
