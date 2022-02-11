#include "mylib/math/glmath.hpp"

glm::vec3 getBarycentricCoords(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& p)
{
    glm::vec3 v0 {b - a}, v1 {c - a}, v2 {p - a};

    float invDen {1.0f / (v0.x * v1.y - v1.x * v0.y)};
    float v {(v2.x * v1.y - v1.x * v2.y) * invDen};
    float w {(v0.x * v2.y - v2.x * v0.y) * invDen};
    float u {1.0f - v - w};
    
    return glm::vec3{v, w, u};
};

