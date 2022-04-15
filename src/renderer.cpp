#include "minecraft/rendering/renderer.hpp"
#include "minecraft/data/vertices.hpp"
#include "minecraft/audio/sound.hpp"
#include "minecraft/data/uniformbuffer.h"
#include "minecraft/math/glmath.hpp"
#include "minecraft/data/vertices.hpp"
#include <cstdio>

static constexpr float strideToNextBlock {0.5f};

static constexpr size_t chunkPosSize {posVerticesSize * chunkVolume * sizeof(float)},
               chunkTexSize {textureVerticesSize * chunkVolume * sizeof(float)},
               chunkLightDirSize {lightDirVerticesSize * chunkVolume * sizeof(float)},
               chunkVisibilitySize {visibleVerticesSize * chunkVolume * sizeof(float)};
    
static constexpr size_t verticesBytes {chunkPosSize + chunkTexSize + chunkLightDirSize + chunkVisibilitySize};

/**
 * Initializes the shaders, blocks and their positions, as well as the 
 * vertex buffer data.
 */
Renderer::Renderer() noexcept : 
cubeShader {"shaders/block/blockvertexshader.vert", "shaders/block/blockfragmentshader.frag"},
lightSource {[this]() {
    constexpr LightComponents components {.ambient = {0.25f, 0.25f, 0.25f}, 
                                          .specular = {1.0f, 1.0f, 1.0f}, 
                                          .diffuse = {0.7f, 0.7f, 0.7f}};

    constexpr glm::vec3 direction {-1.0f, -3.0f, -1.0f};
    constexpr glm::vec3 position {1.0f, 3.0f, 1.0f};
    return Lighting{components, direction, position};
}()},
chunk {BlockName::Grass_Block, BlockName::Dirt_Block}
{
    
    // Create vertex array and bind for the upcoming vertex buffer
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    chunk.modifyChunk(15, 15, 15, Block{BlockName::Dirt_Block}, {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f});
    // Create vertex buffer
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    

    // First allocate enough data for the buffer to store
    constexpr auto vertexData = nullptr;
    glBufferData(GL_ARRAY_BUFFER, verticesBytes, vertexData, GL_DYNAMIC_DRAW);

    // Now fill in the buffer's data
    glBufferSubData(GL_ARRAY_BUFFER, 0, chunkPosSize, &chunk.getVertices().position[0]);
    glBufferSubData(GL_ARRAY_BUFFER, chunkPosSize, chunkTexSize, &chunk.getVertices().texture[0]);
    glBufferSubData(GL_ARRAY_BUFFER, chunkPosSize + chunkTexSize, chunkLightDirSize, &chunk.getVertices().lightDirection[0]);
    glBufferSubData(GL_ARRAY_BUFFER, chunkPosSize + chunkTexSize + chunkLightDirSize, chunkVisibilitySize, 
                    &chunk.getVertices().visibility[0]);

    constexpr auto isNormalized = GL_FALSE;
    glEnableVertexArrayAttrib(vertexBuffer, 0);
    glVertexAttribPointer(0, positionAttributeSize, GL_FLOAT, isNormalized, 
                          positionAttributeSize * sizeof(float), nullptr);

    glEnableVertexArrayAttrib(vertexBuffer, 1);
    glVertexAttribPointer(1, textureAttributeSize, GL_FLOAT, isNormalized, 
                          textureAttributeSize * sizeof(float), reinterpret_cast<const void*>(chunkPosSize));

    glEnableVertexArrayAttrib(vertexBuffer, 2);
    glVertexAttribPointer(2, lightAttributeSize, GL_FLOAT, isNormalized, 
                          lightAttributeSize * sizeof(float), reinterpret_cast<const void*>(chunkPosSize + chunkTexSize));

    glEnableVertexArrayAttrib(vertexBuffer, 3);
    glVertexAttribPointer(3, visibleAttributeSize, GL_FLOAT, isNormalized, visibleAttributeSize * sizeof(float),
                          reinterpret_cast<const void*>(chunkPosSize + chunkTexSize + chunkLightDirSize));
    
    cubeShader.useShader(); 
    lightSource.shaderProgramLightSource(cubeShader);

    cubeShader.setInt("allTextures", 0);

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


void Renderer::update() noexcept
{

}

/**
 * Draws all of the chunks.
 */
void Renderer::draw() const noexcept 
{
    constexpr float ambient {1.2f};
    glm::mat4 model {1.0f};
    glm::vec3 blockPos {0.0f, 0.0f, 0.0f};
    glm::translate(model, blockPos);
    cubeShader.useShader();
    cubeShader.setMat4("model", model);
    cubeShader.setFloat("material.ambient", ambient);

    glDrawArrays(GL_TRIANGLES, 0, chunkVolume * attributesToFormCube);
}

