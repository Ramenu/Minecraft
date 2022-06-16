#ifndef MC_PERLIN_HPP
#define MC_PERLIN_HPP

#include "glm/vec2.hpp"
#include <array>

extern std::array<glm::vec2, 4> generate2DGradients() noexcept;
extern float perlin(float p1, float p2, const std::array<glm::vec2, 4> &gradients) noexcept;

#endif // MC_PERLIN_HPP