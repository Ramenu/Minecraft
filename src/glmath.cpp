#include "minecraft/math/glmath.hpp"

#include "misc/boilerplate/glm_noerr.hpp"
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
        static constexpr int DIRECTIONS_IN_3D {6};
        const glm::vec3 normVec {glm::normalize(vec)};
        
        Direction nearestDirection {};
        float dotOfClosest {glm::dot(DIRECTIONS[0], normVec)};

        // Iterate over all the directions and check which direction is the closest
        for (std::uint32_t i {1}; i < DIRECTIONS_IN_3D; ++i)
        {
            const float dot {glm::dot(DIRECTIONS[i], normVec)};
            if (dot > dotOfClosest)
            {
                nearestDirection = static_cast<Direction>(i);
                dotOfClosest = dot;
            }
        }
        return nearestDirection;
    }

}