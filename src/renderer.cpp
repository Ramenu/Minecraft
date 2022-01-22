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
cubeShader {"shaders/block/blockvertexshader.vs", "shaders/block/blockfragmentshader.fs"},
lightShader {"shaders/light/lightvertexshader.vs", "shaders/light/lightfragmentshader.fs"}
{
    // Create our buffers and store the attribute data in them
    glGenVertexArrays(1, &blockVao);
    glGenVertexArrays(1, &lightVao);
    glGenBuffers(1, &vertexBuffer);
    glBindVertexArray(blockVao);
    loadVertexBuffer(vertexBuffer, sizeof(cubeVertices), cubeVertices);
    setAttributes(3, 2); // 3 = position coordinates, 2 = texture coordinates 
    enableVAOAttributes(2);

    cubeShader.useShader(); // Use the cube cubeShader program
    cubeShader.setVec3("objectColor", {1.0f, 0.5f, 0.31f});
    cubeShader.setVec3("lightColor", {1.0f, 1.0f, 1.0f});

    // Load in the texture atlas
    unsigned int textureAtlas;
    glGenTextures(1, &textureAtlas);
    createTexture("textures/textureatlas.jpg", textureAtlas);
    cubeShader.setInt("allTextures", 0);

    // Create the projection matrix which defines the visible space
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), static_cast<float>(window->screenWidth)/ static_cast<float>(window->screenHeight), 0.1f, 100.0f);
    cubeShader.setMat4("projection", proj);
    
    // Identity matrix
    glm::mat4 model = glm::mat4(1.0f);
    cubeShader.setMat4("model", model);

    // Same process again... for the light cubeShader
    
    glBindVertexArray(lightVao);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // Do not need to store the buffer data into it, since we already did it for the cube
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    lightShader.useShader();
    lightShader.setMat4("projection", proj);
    lightShader.setMat4("model", model);
}

/* Class destructor for Renderer. */
Renderer::~Renderer()
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &blockVao);
    glDeleteVertexArrays(1, &lightVao);
}

/* Draws a 5x0x5 chunk of the block passed. */
void Renderer::drawChunk(const Block& block)
{
    glBindVertexArray(blockVao);
    cubeShader.useShader();
    float x {}, z {};
    glm::mat4 model;
    for (unsigned int i {}; i < 5; i++)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, {x, 0.0f, 0.0f});
        cubeShader.setMat4("model", model);
        block.drawBlock();
        for (unsigned int j {}; j < 5; j++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, {x, 0.0f, z});
            cubeShader.setMat4("model", model);
            block.drawBlock();
            z += 0.5f;
        }
        x += 0.5f;
        z = 0;
    }
}

void Renderer::drawLightSource()
{
    lightShader.useShader();
    glm::mat4 model {glm::mat4(1.0f)};
    model = glm::translate(model, {1.0f, 5.0f, 0.5f});
    lightShader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer::updateView(glm::mat4& viewMatrix)
{
    glBindVertexArray(lightVao);
    cubeShader.useShader();
    cubeShader.setMat4("view", viewMatrix);
    lightShader.useShader();
    lightShader.setMat4("view", viewMatrix);
}

