#include "minecraft/rendering/renderer.hpp"
#include "minecraft/block/face.h"
#include "minecraft/math/frustum.hpp"
#include <cstdio>


static constexpr float highlightedAmbient {1.9f};
static constexpr float noOfChunksOnStart {4.0f};

/**
 * Initializes the shaders, blocks and their positions, as well as the 
 * vertex buffer data.
 */
Renderer::Renderer() noexcept : 
cubeShader {"shaders/block/blockvertexshader.vert", "shaders/block/blockfragmentshader.frag"},
lightSource {[this]() noexcept {
    static constexpr LightComponents components {.ambient = {0.25f, 0.25f, 0.25f}, 
                                                 .specular = {1.0f, 1.0f, 1.0f}, 
                                                 .diffuse = {0.7f, 0.7f, 0.7f}};
    static constexpr glm::vec3 direction {-1.0f, -3.0f, -1.0f};
    static constexpr glm::vec3 position {1.0f, 3.0f, 1.0f};
    return Lighting{components, direction, position};
}()}
{
    for (float x {}; x < noOfChunksOnStart; x += 1.0f)
        for (float z {}; z < noOfChunksOnStart; z += 1.0f)
            allChunks[{static_cast<size_t>(x), 0, static_cast<size_t>(z)}].initChunk({x, 0, z});
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


/**
 * Updates all of the active chunks.
 * Should be called only if an update
 * is required. 
 */
void Renderer::updateActiveChunks() noexcept
{
    for (const auto&[chunkPos, chunk]: allChunks)
    {
        if (chunkPos.x > 0)
        {
            const Chunk* const chunkX {&allChunks[{chunkPos.x - 1, chunkPos.y, chunkPos.z}]};
            chunk.updateChunkVisibilityToNeighbor(*chunkX, LeftFace);
            chunkX->updateChunkVisibilityToNeighbor(chunk, RightFace);
        } 
        if (chunkPos.y > 0)
        {
            const Chunk* const chunkY {&allChunks[{chunkPos.x, chunkPos.y - 1, chunkPos.z}]};
            chunk.updateChunkVisibilityToNeighbor(*chunkY, BottomFace);
            chunkY->updateChunkVisibilityToNeighbor(chunk, TopFace);
        }
        if (chunkPos.z > 0)
        {
            const Chunk* const chunkZ {&allChunks[{chunkPos.x, chunkPos.y, chunkPos.z - 1}]};
            chunk.updateChunkVisibilityToNeighbor(*chunkZ, BackFace);
            chunkZ->updateChunkVisibilityToNeighbor(chunk, FrontFace);
        } 
    }
}

/**
 * Updates the chunks visibility adjacent to
 * the one located at the key given.
 */
void Renderer::updateAdjacentChunks(const glm::u64vec3 &key) noexcept
{
    const Chunk* const chosenChunk {&allChunks[key]};

    if (key.x > 0)
        allChunks[{key.x - 1, key.y, key.z}].updateChunkVisibilityToNeighbor(*chosenChunk, RightFace);

    if (allChunks.find({key.x + 1, key.y, key.z}) != allChunks.end())
        allChunks[{key.x + 1, key.y, key.z}].updateChunkVisibilityToNeighbor(*chosenChunk, LeftFace);

    if (key.y > 0)
        allChunks[{key.x, key.y - 1, key.z}].updateChunkVisibilityToNeighbor(*chosenChunk, TopFace);

    if (allChunks.find({key.x, key.y + 1, key.z}) != allChunks.end())
        allChunks[{key.x, key.y + 1, key.z}].updateChunkVisibilityToNeighbor(*chosenChunk, BottomFace);

    if (key.z > 0)
        allChunks[{key.x, key.y, key.z - 1}].updateChunkVisibilityToNeighbor(*chosenChunk, FrontFace);

    if (allChunks.find({key.x, key.y, key.z + 1}) != allChunks.end())
        allChunks[{key.x, key.y, key.z + 1}].updateChunkVisibilityToNeighbor(*chosenChunk, BackFace);
}

/**
 * Updates the state of the renderer.
 */
void Renderer::update() noexcept
{
    bool updateNearChunks {};
    allChunks[{0, 0, 0}].updateChunk(updateNearChunks);

    if (updateNearChunks)
        updateAdjacentChunks({0, 0, 0});
    
    // This updates all of the chunks, and should be only set to true
    // sparingly.
    if (needsUpdate)
    {
        updateActiveChunks();
        needsUpdate = false;
    }
}

/**
 * Draws all of the chunks.
 */
void Renderer::draw() const noexcept 
{
    for (const auto&[chunkPos, chunk]: allChunks)
        chunk.drawChunk();
}

