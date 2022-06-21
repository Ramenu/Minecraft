#ifndef MC_PLANE_HPP
#define MC_PLANE_HPP

#include "misc/boilerplate/glm_noerr.hpp"
#include <cstdio>

class Plane
{
    public:
        Plane() = default;
        inline Plane(const glm::vec3 &vec, const glm::vec3 &norm) noexcept :
            normal {norm},
            distance {glm::dot(normal, vec)} {}
        glm::vec3 normal;
        float distance;
        inline float getSignedDistanceToPlane(const glm::vec3 &point) const noexcept {
            const float dist {glm::dot(normal, point) - distance};
            //printf("%f\n", static_cast<double>(dist));
            return dist;
        }
};

#endif // MC_PLANE_HPP
