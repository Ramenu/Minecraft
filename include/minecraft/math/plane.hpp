#ifndef MC_PLANE_HPP
#define MC_PLANE_HPP

#include "misc/boilerplate/glm_noerr.hpp"

class Plane
{
    public:
        Plane() = default;
        inline Plane(const glm::vec3 &vec, const glm::vec3 &norm) noexcept :
            normal {glm::normalize(norm)},
            distance {glm::dot(normal, vec)} {}
        glm::vec3 normal;
        float distance;
};

#endif // MC_PLANE_HPP
