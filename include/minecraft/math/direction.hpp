#ifndef MC_DIRECTION_HPP
#define MC_DIRECTION_HPP

#include "glm/vec3.hpp"

static constexpr glm::vec3 directions[6] {
    {1.0f, 0.0f, 0.0f},
    {-1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, -1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, -1.0f}
};

enum Direction : uint8_t
{
    East,
    West,
    Up,
    Down,
    North,
    South
};

inline constexpr glm::vec3 getDirectionVector(Direction direction) noexcept {
    return directions[static_cast<uint8_t>(direction)];
}

#endif // MC_DIRECTION_HPP
