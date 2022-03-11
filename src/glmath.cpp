#include "minecraft/math/glmath.hpp"
#include "glm/glm.hpp"
#include <cmath>

namespace GLMath
{
    /**
     * Returns the nearest 3D direction the vector
     * passed as parameter is closest to.
     */
    glm::vec3 getNearest3DDirectionTo(const glm::vec3 &vec) noexcept
    {
        #if 1
            glm::vec3 vecNormalized {glm::normalize(vec)};
        #endif
        glm::vec3 directions[6] = {
            {0.0f, 1.0f, 0.0f}, // Top
            {0.0f, -1.0f, 0.0f}, // Bottom
            {0.0f, 0.0f, 1.0f}, // East
            {0.0f, 0.0f, -1.0f}, // West
            {1.0f, 0.0f, 0.0f}, // North
            {-1.0f, 0.0f, 0.0f} // South
        };
        glm::vec3 closestDirection;
        float nearest {glm::dot(vecNormalized, directions[0])};

        // Find which direction the vec is closest to
        // Replace this with binary search
        for (uint8_t i {1}; i < 6; i++)
        {
            const float direction {glm::dot(vecNormalized, directions[i])};
            if (direction > nearest)
            {
                nearest = direction;
                closestDirection = directions[i];
            }  
        }
        return closestDirection;
    }

    glm::vec3 getDirectionOfYaw(float yaw) noexcept
    {
        yaw = fabsf(yaw);
        if (yaw > 60.0f && yaw < 90.0f) 
            return {1.0f, 0.0f, 0.0f};
        return {0.0f, 1.0f, 0.0f};
    }

}