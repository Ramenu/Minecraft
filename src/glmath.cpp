#include "minecraft/math/glmath.hpp"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wduplicated-branches"
#include "glm/glm.hpp"
#pragma GCC diagnostic pop
#include "minecraft/glerror/glerror.hpp"
#include <cmath>

namespace GLMath
{
    /**
     * Returns the nearest 3D direction the vector
     * passed as parameter is closest to..
     */
    Direction getDirectionClosestTo(const glm::vec3 &vec) noexcept
    {
        const glm::vec3 normVec {glm::normalize(vec)};
        
        Direction nearestDirection {};
        float dotOfClosest {glm::dot(directions[0], normVec)};

        // Iterate over all the directions and check which direction is the closest
        for (uint8_t i {1}; i < 6; i++)
        {
            const float dot {glm::dot(directions[i], normVec)};
            if (dot > dotOfClosest)
            {
                nearestDirection = static_cast<Direction>(i);
                dotOfClosest = dot;
            }
        }
        return nearestDirection;
    }


}