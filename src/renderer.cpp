#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "mylib/window.hpp"
#include "mylib/renderer.hpp"
#include "mylib/attribute.hpp"
#include "mylib/vertices.hpp"
#include "mylib/buffers/buffer.hpp"
#include <string>

glm::mat4 Renderer::proj;

/* Creates the projection matrix which defines the visible space. */
void Renderer::initProjection()
{
    proj = glm::perspective(
        glm::radians(45.0f), 
        static_cast<float>(Window::getScreenWidth())/ static_cast<float>(Window::getScreenHeight()), 
        0.1f, 
        100.0f);
}

Renderer::Renderer() : 
cubeShader {"shaders/block/blockvertexshader.vert", "shaders/block/blockfragmentshader.frag"},
playerCamera {-90.0f, 0.0f, 2.5f, 0.1f, 45.0f},
selectedBlock {BlockName::Grass_Block},
lightSource {0.25f, 1.0f, 0.7f, glm::vec3{-1.0f, -3.0f, -1.0f}, glm::vec3{1.0f, 3.0f, 1.0f}}
{
    // Create vertex array and bind for the upcoming vertex buffer
    glGenVertexArrays(1, &blockVao);
    glBindVertexArray(blockVao);
    
    // Create our vertex buffer and store the cube vertices data into it
    uint32_t buffer {};
    bool isStatic {true}, isVertexBuffer {true};
    vertexBuffer = BufferData{buffer, sizeof(cubeVertices), cubeVertices, isStatic, isVertexBuffer};
    Buffer::createBuffer(vertexBuffer);

    // 1 = Position coordinates, 2 = Texture coordinates, 3 = Light reflection coordinates, 4 = Normal direction coordinates
    setAttributes(std::vector<intptr_t>{3, 2, 3}); 
    enableVAOAttributes({0, 1, 2});

    glm::mat3 normalMatrix {glm::transpose(glm::inverse(glm::mat4(1.0f)))}; // No idea what this does yet..
    cubeShader.useShader(); 
    cubeShader.setMat3("normalMatrix", normalMatrix);
    cubeShader.setVec3("viewPos", playerCamera.cameraPos);
    cubeShader.setFloat("material.shine", selectedBlock.blockMaterial.shine);
    cubeShader.setVec3("material.specular", selectedBlock.blockMaterial.specular);
    cubeShader.setInt("material.diffuse", selectedBlock.blockMaterial.diffuse);
    cubeShader.setFloat("material.ambient", selectedBlock.blockMaterial.ambient);
    lightSource.shaderProgramLightSource(cubeShader);

    cubeShader.setInt("allTextures", 0);
    cubeShader.setMat4("projection", proj);

    // Same process again... for the light cubeShader (Don't need this right now since it is a directional light at the moment)
    #if 0
        Lighting::bindLightVAO();
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // Do not need to store the buffer data into it, since we already did it for the cube
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    
        lightSource->lightShader.useShader();
        lightSource->lightShader.setMat4("projection", proj);
    #endif
}

/* Class destructor for Renderer. */
Renderer::~Renderer()
{
    lightSource.removeAllLights();
    glDeleteBuffers(1, &vertexBuffer.buffer);
    glDeleteVertexArrays(1, &blockVao);
}

/* Binds the name of the block passed. */
void Renderer::bindBlock(BlockName block)
{
    selectedBlock = Block{block};
}

/* Draws the selected block on the (X, Y, Z) position passed. */
void Renderer::drawBlock(const glm::vec3& xyzPos)
{
    cubeShader.useShader();
    float ambient {selectedBlock.blockMaterial.ambient};
    if (glm::distance(xyzPos, playerCamera.cameraPos) <= 3.0f)
    {
        // TODO: When the player gets closer to block, make the hitbox wider
        const float dot = glm::dot(glm::normalize(playerCamera.cameraFront), glm::vec3{1.0f, 0.0f, 0.0f});
        glfwSetWindowTitle(Window::getWindow(), std::string{std::to_string(dot)}.c_str());
        if (dot > 0.0f && dot < 0.5f)
            ambient = 1.8f;
    }
    glm::mat4 model {glm::translate(glm::mat4{1.0f}, xyzPos)};
    cubeShader.setMat4("model", model);
    cubeShader.setFloat("material.ambient", ambient);
    selectedBlock.drawBlock();
}

/* Draws a 5x0x5 chunk of the selected block. */
void Renderer::drawChunk()
{
    glBindVertexArray(blockVao);
    cubeShader.useShader();
    float x {}, z {};
    glm::mat4 model;
    for (uint32_t i {}; i < 5; i++)
    {
        model = glm::translate(glm::mat4{1.0f}, {x, 0.0f, 0.0f});
        cubeShader.setMat4("model", model);
        selectedBlock.drawBlock();
        for (uint32_t j {}; j < 5; j++)
        {
            model = glm::translate(glm::mat4{1.0f}, {x, 0.0f, z});
            cubeShader.setMat4("model", model);
            selectedBlock.drawBlock();
            z += 0.5f;
        }
        x += 0.5f;
        z = 0;
    }
}

/* Draws the source of the light, should only be used for debugging or testing. It does not make sense to draw the light source since it
   is a directional light. */
void Renderer::drawLightSource()
{
    Lighting::bindLightVAO();
    lightSource.lightShader.useShader();
    glm::mat4 model {glm::translate(glm::mat4{1.0f}, lightSource.lightPos)};
    lightSource.lightShader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

/* Updates the camera view for the player. */
void Renderer::updateView()
{
    playerCamera.updateCameraPos();
    cubeShader.useShader();
    cubeShader.setMat4("view", playerCamera.view);
    cubeShader.setVec3("viewPos", playerCamera.cameraPos);
    #if 0
        lightSource->lightShader.useShader();
        lightSource->lightShader.setMat4("view", playerCamera.view);
    #endif
}

