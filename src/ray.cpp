#include "glad/glad.h"
#include "minecraft/physics/ray.hpp"
#include "minecraft/window.hpp"
#include "minecraft/attribute.hpp"
#include "minecraft/renderer.hpp"
#if 0
    #include <iostream>
#endif
#include <string>

/**
 * Initializes the origin of the ray, its direction 
 * and the ray's magnitude. Given these three vectors,
 * the end of the ray can be calculated to form the ray.
 */
Ray::Ray(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection, const glm::vec3 &rayLength) : 
origin{rayOrigin}, 
direction{rayDirection}, 
shader{"shaders/line/linevertexshader.vert", "shaders/line/linefragmentshader.frag"}, 
length{rayLength}
{
    // Create vertex array and buffer
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    const glm::vec3 rayEnd{origin + direction * length};
    #if 1
        const float rayVertices[6] =
        {
            origin.x, origin.y, origin.z,
            rayEnd.x, rayEnd.y, 0.0f
        };
    #endif
    uint32_t buffer {};
    const bool staticDrawEnabled {true};
    vertexBuffer = BufferData{buffer, sizeof(rayVertices), static_cast<const float*>(rayVertices), staticDrawEnabled};
    Buffer::createBuffer(vertexBuffer);
    setAttributes(std::vector<int32_t>{3});
    enableVAOAttributes({0,1});
    shader.useShader();
    shader.setMat4("projection", Renderer::projection);

}

/**
 * Deletes the vertex buffer and vertex array upon destruction.
 */
Ray::~Ray() noexcept
{
    glDeleteBuffers(1, &vertexBuffer.buffer);
    glDeleteVertexArrays(1, &vao);
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

