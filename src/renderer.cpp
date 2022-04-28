#include "minecraft/rendering/renderer.hpp"
#include "minecraft/data/vertices.hpp"
#include "minecraft/audio/sound.hpp"
#include "minecraft/math/glmath.hpp"
#include "minecraft/data/vertices.hpp"
#include <cstdio>

static constexpr float strideToNextBlock {0.5f};

static constexpr float highlightedAmbient {1.9f};

/**
 * Initializes the shaders, blocks and their positions, as well as the 
 * vertex buffer data.
 */
Renderer::Renderer() noexcept : 
cubeShader {"shaders/block/blockvertexshader.vert", "shaders/block/blockfragmentshader.frag"},
lightSource {[this]() {
    static constexpr LightComponents components {.ambient = {0.25f, 0.25f, 0.25f}, 
                                                 .specular = {1.0f, 1.0f, 1.0f}, 
                                                 .diffuse = {0.7f, 0.7f, 0.7f}};

    static constexpr glm::vec3 direction {-1.0f, -3.0f, -1.0f};
    static constexpr glm::vec3 position {1.0f, 3.0f, 1.0f};
    return Lighting{components, direction, position};
}()},
activeChunk {BlockName::Grass_Block, Dirt_Block}
{
    cubeShader.useShader(); 
    lightSource.shaderProgramLightSource(cubeShader);

    cubeShader.setInt("allTextures", 0);

    // Same process again... for the light cubeShader (Don't need this right now since it is a directional light at the moment)
    #if 0
        Lighting::bindLightVAO();
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer.getBuffer()); // Do not need to store the buffer data into it, since we already did it for the cube
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    #endif
}

/**
 * Eliminates the positional light source.
 */
Renderer::~Renderer() noexcept
{
    lightSource.removeAllLights();
}


void Renderer::update() noexcept
{
    activeChunk.updateBlocks();
}

/**
 * Draws all of the chunks.
 */
void Renderer::draw() const noexcept 
{
    activeChunk.drawChunk();
}

