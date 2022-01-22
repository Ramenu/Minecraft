#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "mylib/renderer.hpp"
#include "mylib/attribute.hpp"
#include "mylib/vertices.hpp"
#include "mylib/buffers/buffer.hpp"
#include "mylib/graphics/textures.hpp"
#include "mylib/camera.hpp"

Renderer::Renderer(const Window* window) : 
shader {std::make_unique<Shader>("shaders/vertexshader.vs", "shaders/fragmentshader.fs")}
{
    // Create our buffers and store the attribute data in them
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vertexBuffer);
    glBindVertexArray(vao);
    loadVertexBuffer(vertexBuffer, sizeof(cubeVertices), cubeVertices);
    setAttributes(3, 2);
    enableAttributes(vertexBuffer, 2);

    shader->useShader(); // Use the shader program

    // Load in the texture atlas
    unsigned int textureAtlas;
    glGenTextures(1, &textureAtlas);
    createTexture("textures/textureatlas.jpg", textureAtlas);
    shader->setInt("allTextures", 0);

    // Create the projection matrix which defines the visible space
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), static_cast<float>(window->screenWidth)/ static_cast<float>(window->screenHeight), 0.1f, 100.0f);
    shader->setMat4("projection", proj);
    
    // Identity matrix
    glm::mat4 model = glm::mat4(1.0f);
    shader->setMat4("model", model);
}

/* Class destructor for Renderer. */
Renderer::~Renderer()
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vao);
}

/* Draws a 5x0x5 chunk of the block passed. */
void Renderer::drawChunk(const Block& block)
{
    float x {}, z {};
    glm::mat4 model;
    for (unsigned int i {}; i < 5; i++)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, {x, 0.0f, 0.0f});
        shader->setMat4("model", model);
        block.drawBlock();
        for (unsigned int j {}; j < 5; j++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, {x, 0.0f, z});
            shader->setMat4("model", model);
            block.drawBlock();
            z += 0.5f;
        }
        x += 0.5f;
        z = 0;
    }
}

