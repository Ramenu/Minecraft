#include "glad/glad.h"
#include "mylib/physics/ray.hpp"
#include "mylib/math/glmath.hpp"
#include "mylib/window.hpp"
#include "mylib/attribute.hpp"
#include "mylib/renderer.hpp"
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

/* Draws this Ray from its origin to the direction its facing, with the distance of its length. */
void Ray::drawRay()
{
    /* NOTE: If we make the ray offset from the block z-axis the same as the x-axis it
            will probably appear exactly the same. */
    ray = glm::vec3{origin.x, origin.y - 0.1f, origin.z} + direction;
    #if 0
        glBindVertexArray(vao);
        rayShader.useShader();

        glm::mat4 model {glm::mat4{1.0f}};
        model = glm::translate(model, ray);
        rayShader.setMat4("model", model);

        glDrawArrays(GL_LINES, 0, 2);
    #endif
}

/* Returns true if the ray intersects with vector B, within 
   the range of -0.5 and 0.5. */
bool Ray::intersectsWith(const glm::vec3& b)
{
    return (
        (ray.x >= b.x - 0.5f && ray.x < b.x) &&
        (ray.y >= b.y - 0.5f && ray.y < b.y + 0.5f));
}


/* Returns true if the ray is inside of the triangle defined by pointA, pointB, and pointC. */
bool Ray::isRayInsideTriangle(const glm::vec3 &pointA, const glm::vec3 &pointB, const glm::vec3 &pointC)
{
    glm::vec3 vwu{getBarycentricCoords(pointA, pointB, pointC, origin)};
    return (vwu.x >= 0.0f && vwu.y >= 0.0f && vwu.z >= 0.0f);
}

