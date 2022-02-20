#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "mylib/window.hpp"
#include "mylib/renderer.hpp"
#include "mylib/attribute.hpp"
#include "mylib/vertices.hpp"
#include "mylib/buffers/buffer.hpp"
#include "mylib/gfx/texture.hpp"
#include "mylib/camera.hpp"

glm::mat4 Renderer::proj;

/* Creates the projection matrix which defines the visible space. */
void Renderer::initProjection()
{
    proj = glm::perspective(glm::radians(45.0f), static_cast<float>(Window::screenWidth)/ static_cast<float>(Window::screenHeight), 0.1f, 100.0f);
}

Renderer::Renderer() : 
cubeShader {"shaders/block/blockvertexshader.vert", "shaders/block/blockfragmentshader.frag"},
playerCamera {std::make_unique<Camera>(-90.0f, 0.0f, 2.5f, 0.1f, 45.0f)},
lightSource {std::make_unique<Lighting>(0.25f, 1.0f, 0.7f, glm::vec3(-1.0f, -3.0f, -1.0f), glm::vec3(1.0f, 3.0f, 1.0f))}
{
    // Create our buffers and store the attribute data in them
    glGenVertexArrays(1, &blockVao);
    glGenBuffers(1, &vertexBuffer);
    glBindVertexArray(blockVao);
    loadVertexBuffer(vertexBuffer, sizeof(cubeVertices), cubeVertices);
    setAttributes(std::vector<intptr_t>{3, 2, 3}); // 1 = Position coordinates, 2 = Texture coordinates
    enableVAOAttributes({0, 1, 2});

    glm::mat3 normalMatrix {glm::transpose(glm::inverse(glm::mat4(1.0f)))}; // No idea what this does yet..
    cubeShader.useShader(); 
    cubeShader.setMat3("normalMatrix", normalMatrix);
    cubeShader.setVec3("viewPos", playerCamera->cameraPos);
    lightSource->shaderProgramLightSource(cubeShader);

    // Load in the texture atlas
    unsigned int textureAtlas;
    glGenTextures(1, &textureAtlas);
    createTexture("textures/textureatlas.jpg", textureAtlas);
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
    lightSource->removeAllLights();
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &blockVao);
}

void Renderer::bindBlock(BlockName block)
{
    selectedBlock = Block(block);
}

/* Draws the selected block on the (X, Y, Z) position passed. */
void Renderer::drawBlock(glm::vec3&& xyzPos)
{
    glBindVertexArray(blockVao);
    cubeShader.useShader();
    glm::mat4 model {glm::translate(glm::mat4(1.0f), xyzPos)};
    cubeShader.setMat4("model", model);
    selectedBlock.drawBlock();
}

/* Draws a 5x0x5 chunk of the selected block. */
void Renderer::drawChunk()
{
    glBindVertexArray(blockVao);
    cubeShader.useShader();
    float x {}, z {};
    glm::mat4 model;
    for (unsigned int i {}; i < 5; i++)
    {
        model = glm::translate(glm::mat4(1.0f), {x, 0.0f, 0.0f});
        cubeShader.setMat4("model", model);
        selectedBlock.drawBlock();
        for (unsigned int j {}; j < 5; j++)
        {
            model = glm::translate(glm::mat4(1.0f), {x, 0.0f, z});
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
    lightSource->lightShader.useShader();
    glm::mat4 model {glm::translate(glm::mat4(1.0f), lightSource->lightPos)};
    lightSource->lightShader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

/* Updates the camera view for the player. */
void Renderer::updateView()
{
    playerCamera->updateCameraPos();
    cubeShader.useShader();
    cubeShader.setMat4("view", playerCamera->view);
    cubeShader.setVec3("viewPos", playerCamera->cameraPos);
    #if 0
        lightSource->lightShader.useShader();
        lightSource->lightShader.setMat4("view", playerCamera->view);
    #endif
}

