/**
 * ONLY USED FOR TESTING!!!!!!
 */

#include "glad/glad.h"
#include "minecraft/ray.hpp"
#include "minecraft/window/window.hpp"
#include "minecraft/rendering/renderer.hpp"
#if 0
    #include <iostream>
#endif
#include <string>
#include <fstream>
#include <ostream>
#include <sstream>

/**
 * Initializes the origin of the ray, its direction 
 * and the ray's magnitude. Given these three vectors,
 * the end of the ray can be calculated to form the ray.
 */
void Ray::initRay(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection, const glm::vec3 &rayLength)
{
    origin = rayOrigin;
    direction = rayDirection;
    length = rayLength;

    // make shader
    std::stringstream vertexShaderStream, fragmentShaderStream;
    std::ifstream vertexShaderFile, fragmentShaderFile;

    vertexShaderFile.open("./shaders/line/linevertexshader.vert");
    fragmentShaderFile.open("./shaders/line/linefragmentshader.frag");

    // Read file contents into the string streams
    vertexShaderStream << vertexShaderFile.rdbuf();
    fragmentShaderStream << fragmentShaderFile.rdbuf();

    vertexShaderFile.close();
    fragmentShaderFile.close();
    
    // Compile vertex shader
    const std::string vertexShaderCode {vertexShaderStream.str()};
    const char *cstrVertexShaderCode {vertexShaderCode.c_str()};
    const GLuint vertexShader {glCreateShader(GL_VERTEX_SHADER)};
    glShaderSource(vertexShader, 1, &cstrVertexShaderCode, NULL);
    glCompileShader(vertexShader);

    // Compile fragment shader
    const std::string fragmentShaderCode {fragmentShaderStream.str()};
    const char *cstrFragmentShaderCode {fragmentShaderCode.c_str()};
    const GLuint fragmentShader {glCreateShader(GL_FRAGMENT_SHADER)};
    glShaderSource(fragmentShader, 1, &cstrFragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    
    lineProgram = glCreateProgram();

    // Attach the shaders together and link the program (and check for errors)
    glAttachShader(lineProgram, vertexShader);
    glAttachShader(lineProgram, fragmentShader);
    glLinkProgram(lineProgram);

    glDeleteShader(vertexShader); 
    glDeleteShader(fragmentShader);

    // Create vertex array and buffer
    glUseProgram(lineProgram);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    const glm::vec3 rayEnd{origin + direction * length};
    #if 1
        const float rayVertices[20] =
        {
            origin.x, origin.y, origin.z,    0.0f, 0.0f, 1.0f,     0.0f, 0.0f, 0.0f,     0.0f,
            rayEnd.x, rayEnd.y, rayEnd.z,    1.0f, 0.0f, 0.0f,     1.0f, 1.0f, 1.0f,     1.0f,
        };
    #endif
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rayVertices), static_cast<const float*>(rayVertices), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), reinterpret_cast<const void*>(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), reinterpret_cast<const void*>(3));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), reinterpret_cast<const void*>(6));
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 10 * sizeof(float), reinterpret_cast<const void*>(9));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
}

/**
 * Deletes the vertex buffer and vertex array upon destruction.
 */
Ray::~Ray() noexcept
{
    glDeleteBuffers(1, &vertexBuffer);
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
void Ray::updateRay(float xRotationRadians, [[maybe_unused]] float yRotationRadians, [[maybe_unused]] float zRotationRadians) 
{ 
    glBindVertexArray(vao);
    glUseProgram(lineProgram);
    glm::mat4 model {glm::translate(glm::mat4{1.0f}, glm::vec3{ray.x, ray.y - 0.1f, ray.z})};
    glm::mat4 rotationModelX {glm::rotate(model, xRotationRadians ,glm::vec3{0.0f, 1.0f, 0.0f})};
    glm::mat4 rotationModelY {glm::rotate(rotationModelX, yRotationRadians ,glm::vec3{-1.0f, 0.0f, 0.0f})};
    glUniformMatrix4fv(glGetUniformLocation(lineProgram, "model"), 1, GL_FALSE, &rotationModelY[0][0]);
    glDrawArrays(GL_LINES, 0, 2);

}