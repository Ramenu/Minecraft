#include "minecraft/math/radians.hpp"
#include "glm/trigonometric.hpp"

/**
 * Converts the given angle
 * into radians and constructs
 * the object.
 */
Radians::Radians(float angle) noexcept :
radians {glm::radians(angle)}
{

}