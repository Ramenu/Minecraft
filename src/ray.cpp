#include "minecraft/physics/ray.hpp"
#if 0
    #include <iostream>
#endif

/**
 * Initializes the origin of the ray, its direction 
 * and the ray's magnitude. Given these three vectors,
 * the end of the ray can be calculated to form the ray.
 */
Ray::Ray(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection, const glm::vec3 &rayLength) : 
origin{rayOrigin}, 
direction{rayDirection}, 
length{rayLength}
{

}

/**
 * Returns true if the ray and vector B are within
 * a distance less than or equal to 0.5.
 */
bool Ray::intersectsWith(const glm::vec3 &b) const noexcept
{
    constexpr float blockWidth {0.5f};
    return (
        (ray.x >= b.x - blockWidth && ray.x < b.x) &&
        (ray.y >= b.y - blockWidth && ray.y < b.y + blockWidth));
}


/**
 * Updates the position of the ray.
 */
void Ray::updateRay() { ray = glm::vec3{origin.x, origin.y - 0.1f, origin.z} + direction;}

