#ifndef MC_PLANE_HPP
#define MC_PLANE_HPP

#include "misc/boilerplate/glm_noerr.hpp"

class Plane
{
    public:
        Plane() = default;
        inline Plane(const glm::vec3 &vec, const glm::vec3 &norm) noexcept :
            normal {glm::normalize(vec)},
            distance {glm::dot(vec, norm)} {}
        glm::vec3 normal {0.0f, 1.0f, 0.0f};
        float distance {0.0f};
};

#endif // MC_PLANE_HPP
