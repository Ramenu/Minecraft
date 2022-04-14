#include "minecraft/rendering/renderer.hpp"
#include "minecraft/data/vertices.hpp"
#include "minecraft/audio/sound.hpp"
#include "minecraft/data/uniformbuffer.h"
#include "minecraft/math/glmath.hpp"
#include "minecraft/data/vertices.hpp"
#include <cstdio>
#include <algorithm>

static constexpr float strideToNextBlock {0.5f};

/**
 * Initializes the shaders, blocks and their positions, as well as the 
 * vertex buffer data.
 */
Renderer::Renderer() noexcept : 
playerCamera {CameraSettings{.yaw = 90.0f, .pitch = 0.0f, .sensitivity = 0.1f}},
cubeShader {"shaders/block/blockvertexshader.vert", "shaders/block/blockfragmentshader.frag"},
lightSource {[this]() {
    constexpr LightComponents components {.ambient = {0.25f, 0.25f, 0.25f}, 
                                          .specular = {1.0f, 1.0f, 1.0f}, 
                                          .diffuse = {0.7f, 0.7f, 0.7f}};

    constexpr glm::vec3 direction {-1.0f, -3.0f, -1.0f};
    constexpr glm::vec3 position {1.0f, 3.0f, 1.0f};
    return Lighting{components, direction, position};
}()}
{
    
    // Create vertex array and bind for the upcoming vertex buffer
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    // Create vertex buffer
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    std::vector<CubeVertex> chunkVertices {initChunkVertices()};
    CubeVertex cube {chunkVertices[0]};
    for (size_t i {1}; i < chunkVertices.size(); i++)
    {
        cube.positionVertices.insert(cube.positionVertices.end(), 
                                     chunkVertices[i].positionVertices.begin(), 
                                     chunkVertices[i].positionVertices.end());
        
        cube.textureVertices.insert(cube.textureVertices.end(),
                                    chunkVertices[i].textureVertices.begin(),
                                    chunkVertices[i].textureVertices.end());
        
        cube.lightDirectionVertices.insert(cube.lightDirectionVertices.end(),
                                    chunkVertices[i].lightDirectionVertices.begin(),
                                    chunkVertices[i].lightDirectionVertices.end());
    }
    printf("Size of chunk vertices is: %lld\n", chunkVertices.size());

    constexpr size_t verticesBytes {noOfVertices * sizeof(float)};

    constexpr auto vertexData = nullptr;
    const size_t chunkPosSize {posVerticesSize * sizeof(float) * chunkVertices.size()},
               chunkTexSize {textureVerticesSize * sizeof(float) * chunkVertices.size()},
               chunkLightDirSize {lightDirVerticesSize * sizeof(float) * chunkVertices.size()};

    glBufferData(GL_ARRAY_BUFFER, verticesBytes * chunkVertices.size(), vertexData, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, chunkPosSize, &cube.positionVertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, chunkPosSize, chunkTexSize, &cube.textureVertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, chunkPosSize + chunkTexSize, chunkLightDirSize, &cube.lightDirectionVertices[0]);

    constexpr auto isNormalized = GL_FALSE;
    glEnableVertexArrayAttrib(vertexBuffer, 0);
    glVertexAttribPointer(0, positionAttributeSize, GL_FLOAT, isNormalized, 
                          3 * sizeof(float), reinterpret_cast<const void*>(0));

    glEnableVertexArrayAttrib(vertexBuffer, 1);
    glVertexAttribPointer(1, textureAttributeSize, GL_FLOAT, isNormalized, 
                          2 * sizeof(float), reinterpret_cast<const void*>(chunkPosSize));

    glEnableVertexArrayAttrib(vertexBuffer, 2);
    glVertexAttribPointer(2, lightAttributeSize, GL_FLOAT, isNormalized, 
                          3 * sizeof(float), reinterpret_cast<const void*>(chunkPosSize + chunkTexSize));
    

    glm::mat3 normalMatrix {glm::transpose(glm::inverse(glm::mat4(1.0f)))}; // No idea what this does yet..
    cubeShader.useShader(); 
    cubeShader.setMat3("normalMatrix", normalMatrix);
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
    glDeleteVertexArrays(1, &vertexArray);
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

void Renderer::draw() const noexcept 
{
    glm::mat4 model {1.0f};
    glm::vec3 blockPos {0.0f, 0.0f, 0.0f};
    glm::translate(model, blockPos);
    cubeShader.useShader();
    cubeShader.setMat4("model", model);

    glDrawArrays(GL_TRIANGLES, 0, attributesToFormCube * chunkVolume * 2 * 2);
}

