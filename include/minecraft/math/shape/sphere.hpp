#ifndef MC_SPHERE_HPP
#define MC_SPHERE_HPP

#include "glm/vec3.hpp"
#include "minecraft/math/plane.hpp"

class Sphere
{
    public:
        glm::vec3 center;
        float radius;
        inline bool isOnForwardPlane(const Plane &plane) const noexcept {
            return plane.getSignedDistanceToPlane(center) > -radius;
        }
};

#endif // MC_SPHERE_HPP