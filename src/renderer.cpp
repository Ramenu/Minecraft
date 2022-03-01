#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "minecraft/window.hpp"
#include "minecraft/renderer.hpp"
#include "minecraft/attribute.hpp"
#include "minecraft/vertices.hpp"
#include "minecraft/buffers/buffer.hpp"
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
selectedBlock {BlockName::Grass_Block, false},
lightSource {0.25f, 1.0f, 0.7f, glm::vec3{-1.0f, -3.0f, -1.0f}, glm::vec3{1.0f, 3.0f, 1.0f}},
blocks {25}
{
    bool playCreationSFX {false};
    std::fill(blocks.begin(), blocks.end(), Block{BlockName::Grass_Block, playCreationSFX}); // Initialize a vector of 25 grass blocks

    /* Initialize the position of the blocks at their respective positions. This is far from the most efficient, clean and practical solution, 
       but this is only for prototyping and checking that it works. Besides, this is called in this constructor only. */
    float x {}, z {};
    uint32_t i {};
    for (uint32_t k {}; k < 5; k++)
    {
        blocks.at(i).position = {x, 0.0f, 0.0f};
        for (uint32_t j {}; j < 5; j++)
        {
            blocks.at(i).position = {x, 0.0f, z};
            z += 0.5f;
            i++;
        }
        x += 0.5f;
        z = 0;
    }


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
    selectedBlock = Block{block, false};
}

/* Returns true if the block located at 'blockCoords' intersects with the camera ray. */
bool Renderer::canHighlightBlock(const glm::vec3 &blockCoords)
{
    const float distance {glm::distance(blockCoords, playerCamera.cameraPos)};
    if (distance <= 2.0f)
    {
        if (playerCamera.cameraRay.intersectsWith(blockCoords))
        {
            const float distanceBetween {glm::distance(playerCamera.cameraRay.getRay(), blockCoords)};
            const float nextBlock {glm::distance(playerCamera.cameraRay.getRay(), glm::vec3{blockCoords.x, blockCoords.y, blockCoords.z + 0.5f})};
            return (distanceBetween <= 0.5f && distanceBetween <= nextBlock);
        }
    }
    return false;
}

/* Draws the selected block on the (X, Y, Z) position passed. */
void Renderer::drawBlock(Block &block)
{
    float ambient {selectedBlock.blockMaterial.ambient};
    if (canHighlightBlock(block.position))
    {
        static int oldState = GLFW_RELEASE;
        int newState = glfwGetMouseButton(Window::getWindow(), GLFW_MOUSE_BUTTON_RIGHT);
        ambient = 1.8f;

        // Destroy the block on click
        if (glfwGetMouseButton(Window::getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            block.playDestroyedSound();
            block.isDestroyed = true;
            return;
        }
        else if (newState == GLFW_RELEASE && oldState == GLFW_PRESS)
        {
            bool playSFX = true;
            Block blockPlaced {BlockName::Cobblestone_Block, playSFX};
            blockPlaced.position = {block.position.x, block.position.y + 1.0f, block.position.z};
            blocks.emplace_back(blockPlaced);
        }
        oldState = newState;
    }
    glm::mat4 model {glm::translate(glm::mat4{1.0f}, block.position)};
    cubeShader.setMat4("model", model);
    cubeShader.setFloat("material.ambient", ambient);
    cubeShader.setFloat("textureY", block.getTextureID());
    block.draw();
}

/* Draws all of the blocks available in the vector. */
void Renderer::drawAllBlocks()
{
    for (size_t i {}; i < blocks.size(); i++)
    {
        drawBlock(blocks[i]);

        // Check to see if the block was destroyed by the player, if so, remove it from the vector
        if (blocks[i].isDestroyed)
            blocks.erase(blocks.begin() + i);
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

/* Updates the camera view for the player, and updates all the shaders to the updated position of the camera. */
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

