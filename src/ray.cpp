#include "glad/glad.h"
#include "minecraft/physics/ray.hpp"
#include "minecraft/window.hpp"
#include "minecraft/attribute.hpp"
#include "minecraft/renderer.hpp"
#if 0
    #include <iostream>
#endif
#include <string>

/* Constructor for the Ray object. */
Ray::Ray(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, const glm::vec3& rayLength) : 
origin{rayOrigin}, 
direction{rayDirection}, 
rayShader{"shaders/line/linevertexshader.vert", "shaders/line/linefragmentshader.frag"}, 
length{rayLength}
{
    // Create vertex array and buffer
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glm::vec3 rayEnd{origin + direction * length};
    #if 1
        const float rayVertices[6] =
        {
            origin.x, origin.y, origin.z,
            rayEnd.x, rayEnd.y, 0.0f
        };
    #endif
    uint32_t buffer {};
    bool doStaticDraw {true}, isVertexBuffer {true};
    vertexBuffer = BufferData{buffer, sizeof(rayVertices), rayVertices, doStaticDraw, isVertexBuffer};
    Buffer::createBuffer(vertexBuffer);
    setAttributes(std::vector<intptr_t>{3});
    enableVAOAttributes({0,1});
    rayShader.useShader();
    rayShader.setMat4("projection", Renderer::getProjection());

}

/* Destructor for the Ray object. Deallocates the ray's buffer and deletes the vertex array. */
Ray::~Ray()
{
    glDeleteBuffers(1, &vertexBuffer.buffer);
    glDeleteVertexArrays(1, &vao);
}

/* Returns true if the ray intersects with vector B, within 
   the range of -0.5 and 0.5. */
bool Ray::intersectsWith(const glm::vec3& b)
{
    return (
        (ray.x >= b.x - 0.5f && ray.x < b.x) &&
        (ray.y >= b.y - 0.5f && ray.y < b.y + 0.5f));
}


/* Updates the position of the ray. */
void Ray::updateRay() { ray = glm::vec3{origin.x, origin.y - 0.1f, origin.z} + direction;}

