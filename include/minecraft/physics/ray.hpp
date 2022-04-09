#ifndef RAY_HPP
#define RAY_HPP

#include "glm/vec3.hpp"


class Ray
{
    public:
        constexpr Ray(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection) noexcept : ray {rayOrigin + rayDirection} {}
        inline void updateRay(const glm::vec3 &origin, const glm::vec3 &direction) 
        {
            ray = glm::vec3{origin.x, origin.y - 0.1f, origin.z} + direction;
        }
        inline glm::vec3 getRay() const {return ray;}
        inline bool intersectsWith(const glm::vec3 &b) const 
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
