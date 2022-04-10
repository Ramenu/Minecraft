#include "minecraft/rendering/renderer.hpp"
#include "minecraft/window/window.hpp"
#include "minecraft/data/vertices.hpp"
#include "minecraft/buffer/buffer.hpp"
#include "minecraft/audio/sound.hpp"
#include "minecraft/data/uniformbuffer.h"
#include "minecraft/math/glmath.hpp"
#include <cstdio>

static constexpr float strideToNextBlock {0.5f};
const glm::mat4 Renderer::projection {[]{
        constexpr double fov {glm::radians(45.0)}, 
        aspectRatio {Window::width/Window::height}, 
        near {0.1}, 
        far {100.0};
        return glm::perspective(fov, aspectRatio, near, far);
    }()
};



/**
 * Initializes the shaders, blocks and their positions, as well as the 
 * vertex buffer data.
 */
Renderer::Renderer() noexcept : 
playerCamera {CameraSettings{.yaw = 90.0f, .pitch = 0.0f, .sensitivity = 0.1f}},
cubeShader {"shaders/block/blockvertexshader.vert", "shaders/block/blockfragmentshader.frag"},
lightSource {[this]() {
    constexpr glm::vec3 ambient {0.25f, 0.25f, 0.25f};
    constexpr glm::vec3 specular {1.0f, 1.0f, 1.0f};
    constexpr glm::vec3 diffuse {0.7f, 0.7f, 0.7f};
    constexpr LightComponents components {ambient, specular, diffuse};

    constexpr glm::vec3 direction {-1.0f, -3.0f, -1.0f};
    constexpr glm::vec3 position {1.0f, 3.0f, 1.0f};
    return Lighting{components, direction, position};
}()}
{
    
    // Create vertex array and bind for the upcoming vertex buffer
    glGenVertexArrays(1, &blockVao);
    glBindVertexArray(blockVao);

    // Create vertex buffer
    constexpr size_t positionOffset {3}, textureOffset {2}, lightDirectionOffset {3};
    BufferData buf {.size = sizeof(cubeVertices), .data = static_cast<const float*>(cubeVertices)};
    vertexBuffer = Buffer::createVertexBuffer(buf, std::vector<size_t>{positionOffset, textureOffset, lightDirectionOffset});

    glm::mat3 normalMatrix {glm::transpose(glm::inverse(glm::mat4(1.0f)))}; // No idea what this does yet..
    cubeShader.useShader(); 
    cubeShader.setMat3("normalMatrix", normalMatrix);
    cubeShader.setVec3("viewPos", playerCamera.cameraPos);
    lightSource.shaderProgramLightSource(cubeShader);

    cubeShader.setInt("allTextures", 0);
    // Bind the uniform buffer and fill the data with the projection matrix
    glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &projection[0][0]);

    // Same process again... for the light cubeShader (Don't need this right now since it is a directional light at the moment)
    #if 0
        Lighting::bindLightVAO();
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // Do not need to store the buffer data into it, since we already did it for the cube
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    #endif
}

/**
 * Eliminates the positional light source and deletes
 * the vertex buffer and vertex array.
 */
Renderer::~Renderer() noexcept
{
    lightSource.removeAllLights();
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &blockVao);
}


/**
 * Returns true if the block located at 'blockCoords' intersects with the 
 * camera ray. 
 */
bool Renderer::canHighlightBlock(const glm::vec3 &blockCoords) const noexcept
{
    const float distance {glm::distance(blockCoords, playerCamera.cameraPos)};
    constexpr float playerReachableDistance {2.0f};
    if (distance <= playerReachableDistance)
    {
        if (playerCamera.ray.intersectsWith(blockCoords))
        {
            const float distanceBetween {glm::distance(playerCamera.ray.getRay(), blockCoords)};
            const float nextBlock {glm::distance(playerCamera.ray.getRay(), 
                                   glm::vec3{blockCoords.x, blockCoords.y, blockCoords.z + strideToNextBlock})};

            return (distanceBetween <= strideToNextBlock && distanceBetween <= nextBlock);
        }
    }
    return false;
}

/** 
 * Takes the indice of the block in the vector
 * and draws or destroys it.
 */
void Renderer::drawBlock(Block &block, const glm::vec3 &blockIndex) noexcept
{
    float ambient {1.2f}; // Default ambient level
    const glm::vec3 position {GLMath::getBlockPos(blockIndex)};
    if (canHighlightBlock(position))
    {
        static constinit int oldState = GLFW_RELEASE;
        const int newState = glfwGetMouseButton(Window::window, GLFW_MOUSE_BUTTON_RIGHT);
        ambient = 1.8f;

        // Destroy the block player is facing
        if (glfwGetMouseButton(Window::window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            Sound::playBlockBreakSound(block.name);
            block.name = BlockName::Air_Block;
            return;
        }
        // Place a block
        else if (newState == GLFW_RELEASE && oldState == GLFW_PRESS)
        {
            const glm::vec3 index {blockIndex + (-GLMath::closestDirectionTo(playerCamera.direction.front))};
            if (!Chunk::isOutOfChunk(index))
            {
                // todo: understand the format of the array, how the blocks are placed, etc.
                if (terrain.chunk[index.x][index.y][index.z].name == BlockName::Air_Block)
                {
                    terrain.chunk[index.x][index.y][index.z].name = BlockName::Cobblestone_Block;
                    Sound::playBlockPlacementSound(BlockName::Cobblestone_Block);
                }
            }
        }
        oldState = newState;
    }
    glm::mat4 model {glm::translate(glm::mat4{1.0f}, position)};
    cubeShader.setMat4("model", model);
    cubeShader.setFloat("material.ambient", ambient);
    cubeShader.setFloat("textureY", block.getTexture());

    constexpr uint8_t verticesToBeDrawn {36};
    glDrawArrays(GL_TRIANGLES, 0, verticesToBeDrawn);
}


/**
 * Draws the source of the light, should only be 
 * used for debugging or testing. It does not make 
 * sense to draw the light source since it is a directional light. 
 */
void Renderer::drawLightSource() noexcept
{
    Lighting::bindLightVAO();
    lightSource.lightShader.useShader();
    glm::mat4 model {glm::translate(glm::mat4{1.0f}, lightSource.position)};
    lightSource.lightShader.setMat4("model", model);
    // glDrawArrays(GL_TRIANGLES, 0, 36);
}

/**
 * Updates the camera view for the player, 
 * and updates all the shaders to the updated 
 * position of the camera. 
 */
void Renderer::updateView() noexcept
{
    double xPos, yPos;
    glfwGetCursorPos(Window::window, &xPos, &yPos);
    playerCamera.updateCameraPos(xPos, yPos);
    cubeShader.setMat4("view", playerCamera.getView());
    cubeShader.setVec3("viewPos", playerCamera.cameraPos);
    #if 0
        lightSource->lightShader.useShader();
        lightSource->lightShader.setMat4("view", playerCamera.view);
    #endif
}

/**
 * Draws all of the blocks in the chunk.
 */
void Renderer::drawChunk() noexcept 
{
    for (uint8_t x {}; x < chunkWidth; x++)
    {
        for (uint8_t y {}; y < chunkHeight; y++)
        {
            for (uint8_t z {}; z < chunkLength; z++)
            {
                if (terrain.chunk[x][y][z].name != BlockName::Air_Block)
                    drawBlock(terrain.chunk[x][y][z], glm::vec3{x, y, z});
            }
        }
    }
}

