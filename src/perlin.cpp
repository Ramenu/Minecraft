#include "minecraft/world/perlin.hpp"
#include "minecraft/math/glmath.hpp"
#include <cmath>
#include <cstdlib>


/**
 * Returns a pseudo-randomized 2D unit vector.
 */
static glm::vec2 getRandom2DUnitVector() noexcept {
    static constexpr float ROLL_MAX {2 * M_PIf};
    const float randomAngle {GLMath::randf() * ROLL_MAX};
    return {std::cos(randomAngle), std::sin(randomAngle)};
}

/**
 * Returns an array of 4 pseudo-random gradients.
 */
std::array<glm::vec2, 4> generate2DGradients() noexcept {
    return {
        getRandom2DUnitVector(),
        getRandom2DUnitVector(),
        getRandom2DUnitVector(),
        getRandom2DUnitVector()
    };
}

/**
 * Perlin-noise function, returns a float ranging from [-1.0 .. 1.0].
 * 'p1' and 'p2' should be two arbitary coordinates. An array of 4
 * gradients (i.e., unit vectors) should be passed to the function
 * as well.
 */
float perlin(float p1, float p2, const std::array<glm::vec2, 4> &gradients) noexcept 
{
    const glm::vec2 point {p1*0.01f, p2*0.01f};

    // Compute the distance between the point and each of the gradients
    const float d1 {glm::dot(point, gradients[0])};
    const float d2 {glm::dot(point, gradients[1])};
    const float d3 {glm::dot(point, gradients[2])};
    const float d4 {glm::dot(point, gradients[3])};

    const float step1 {GLMath::smoothstep(0.0f, CHUNK_HEIGHT - 1.0f, p1)};
    const float step2 {GLMath::smoothstep(0.0f, CHUNK_HEIGHT - 1.0f, p2)};
    const float li1 {std::lerp(d1, d2, step1)}, li2 {std::lerp(d3, d4, step1)};
    return std::lerp(li1, li2, step2);
}