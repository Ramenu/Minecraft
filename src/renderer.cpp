#include "minecraft/rendering/renderer.hpp"
#include "minecraft/data/vertices.hpp"
#include "minecraft/audio/sound.hpp"
#include "minecraft/math/glmath.hpp"
#include "minecraft/data/vertices.hpp"
#include "minecraft/rendering/chunk.hpp"
#include "minecraft/block/face.h"
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
    #if 1
    for (float x {}; x < noOfChunksOnStart; x += 1.0f)
        for (float z {}; z < noOfChunksOnStart; z += 1.0f)
            allChunks[{static_cast<size_t>(x), static_cast<size_t>(z)}].initChunk({x, 0.0f, z});
    #else
    allChunks[{0, 0}].initChunk({0.0f, 0.0f, 0.0f});
    #endif

    #if 0
    allChunks[{0, 0}].initChunk({0.0f, 0.0f, 0.0f});
    allChunks[{0, 1}].initChunk({0.0f, 0.0f, 1.0f});
    allChunks[{0, 2}].initChunk({0.0f, 0.0f, 2.0f});
    allChunks[{0, 3}].initChunk({0.0f, 0.0f, 3.0f});
    allChunks[{0, 4}].initChunk({0.0f, 0.0f, 4.0f});
    allChunks[{0, 5}].initChunk({0.0f, 0.0f, 5.0f});
    #else
        #if 0
        allChunks[{0, 0}].initChunk({0.0f, 0.0f, 0.0f});
        allChunks[{1, 0}].initChunk({1.0f, 0.0f, 0.0f});
        allChunks[{2, 0}].initChunk({2.0f, 0.0f, 0.0f});
        allChunks[{3, 0}].initChunk({3.0f, 0.0f, 0.0f});
        allChunks[{4, 0}].initChunk({4.0f, 0.0f, 0.0f});
        allChunks[{5, 0}].initChunk({5.0f, 0.0f, 0.0f});
        #endif
    #endif
    #if 1
    //static constexpr float maxChunkLimit {2.0f};
    #else
    for (size_t i {}; i < 4; i++)
        allChunks.emplace_back(Chunk{});
    allChunks[0].initChunk({0.0f, 0.0f, 0.0f});
    allChunks[1].initChunk({0.0f, 0.0f, 1.0f});
    allChunks[2].initChunk({1.0f, 0.0f, 0.0f});
    allChunks[3].initChunk({1.0f, 0.0f, 1.0f});
    #endif
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
    for (auto&[chunkPos, chunk]: allChunks)
    {
        // Note that y is a subsitute for z since it is a vec2
        const uint64_t z {chunkPos.y};
        if (z > 0)
        {
            chunk.updateChunkVisibilityToNeighbor(allChunks[{chunkPos.x, z - 1}], BackFace);
            allChunks[{chunkPos.x, z - 1}].updateChunkVisibilityToNeighbor(chunk, FrontFace);
        } 
        if (chunkPos.x > 0)
        {
            chunk.updateChunkVisibilityToNeighbor(allChunks[{chunkPos.x - 1, z}], LeftFace);
            allChunks[{chunkPos.x - 1, z}].updateChunkVisibilityToNeighbor(chunk, RightFace);
        } 
    }
}

/**
 * Updates the chunks visibility adjacent to
 * the one located at the key given.
 */
void Renderer::updateAdjacentChunks(const glm::u64vec2 &key) noexcept
{
    const size_t z {key.y};
    const Chunk *chosenChunk {&allChunks[key]};

    if (z > 0)
    {
        //chosenChunk->updateChunkVisibilityToNeighbor(allChunks[{key.x, z - 1}], BackFace);
        allChunks[{key.x, z - 1}].updateChunkVisibilityToNeighbor(*chosenChunk, FrontFace);
    }

    if (allChunks.find({key.x, z + 1}) != allChunks.end())
    {
        //chosenChunk->updateChunkVisibilityToNeighbor(allChunks[{key.x, z + 1}], BackFace);
        allChunks[{key.x, z + 1}].updateChunkVisibilityToNeighbor(*chosenChunk, BackFace);
    }

    if (key.x > 0)
    {
        //chosenChunk->updateChunkVisibilityToNeighbor(allChunks[{key.x - 1, z}], LeftFace);
        allChunks[{key.x - 1, z}].updateChunkVisibilityToNeighbor(*chosenChunk, RightFace);
    }

    if (allChunks.find({key.x + 1, z}) != allChunks.end())
    {
        //chosenChunk->updateChunkVisibilityToNeighbor(allChunks[{key.x + 1, z}], LeftFace);
        allChunks[{key.x + 1, z}].updateChunkVisibilityToNeighbor(*chosenChunk, LeftFace);
    }
}

/**
 * Updates the state of the renderer.
 */
void Renderer::update() noexcept
{
    bool updateNearChunks {};
    allChunks[{0, 0}].updateChunk(updateNearChunks);

    if (updateNearChunks)
        updateAdjacentChunks({0, 0});
    
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
    for (const auto&chunk: allChunks)
        chunk.second.drawChunk();
}

