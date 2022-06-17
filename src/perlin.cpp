#include "minecraft/world/perlin.hpp"
#include "minecraft/math/glmath.hpp"
#include <cmath>
#include <cstdlib>


/**
 * Returns a permutation table
 * (i.e., an array filled with values from 0 to N-1).
 * Values are pseudo-randomly shuffled.
 */
template<typename T, std::size_t N>
requires std::is_arithmetic_v<T>
static std::array<T, N> createPermutationTable() noexcept
{
    std::array<T, N> table;
    for (std::size_t i {}; i < table.size(); ++i)
        table[i] = i;
    std::random_shuffle(table.begin(), table.end());
    return table;
}


static glm::vec2 getRandom2DUnitVector() noexcept {
    static constexpr float ROLL_MAX {2 * M_PIf};
    const float randomAngle {GLMath::randf() * ROLL_MAX};
    return {std::cos(randomAngle), std::sin(randomAngle)};
}

std::array<glm::vec2, 4> generate2DGradients() noexcept {
    return {
        getRandom2DUnitVector(),
        getRandom2DUnitVector(),
        getRandom2DUnitVector(),
        getRandom2DUnitVector()
    };
}

/**
 *
 */
float perlin(float p1, float p2, const std::array<glm::vec2, 4> &gradients) noexcept 
{
    const glm::vec2 point {p1, p2};
    const float d1 {glm::dot(point, gradients[0])};
    const float d2 {glm::dot(point, gradients[1])};
    const float d3 {glm::dot(point, gradients[2])};
    const float d4 {glm::dot(point, gradients[3])};

    const float t1 {GLMath::fade(p1)}, t2 {GLMath::fade(p2)};
    const float li1 {std::lerp(d1, d2, t1)}, li2 {std::lerp(d3, d4, t1)};
    return std::lerp(li1, li2, t2);
}