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
    glm::vec3 closestDirectionTo(const glm::vec3 &vec) noexcept
    {
        const glm::vec3 normVec {glm::normalize(vec)};
        static constexpr glm::vec3 directions[6] {
            {1.0f, 0.0f, 0.0f},
            {-1.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {0.0f, -1.0f, 0.0f},
            {0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, -1.0f}
        };
        glm::vec3 closest {directions[0]};
        float dotOfClosest {glm::dot(closest, normVec)};

        // Iterate over all the directions and check which direction is the closest
        for (uint8_t i {1}; i < 6; i++)
        {
            float dot {glm::dot(directions[i], normVec)};
            if (dot > dotOfClosest)
            {
                closest = directions[i];
                dotOfClosest = dot;
            }
        }
        return closest;
    }

    #if 0
    glm::vec3 nearestBlockTo(const glm::vec3 &vec) noexcept 
    {
        
        
    
    }
    #endif


}