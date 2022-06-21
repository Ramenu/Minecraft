#include "minecraft/rendering/renderer.hpp"
#include "minecraft/block/face.h"
#include "minecraft/math/frustum.hpp"
#include "minecraft/math/glmath.hpp"
#include <cstdio>


static constexpr std::int32_t CHUNKS_ON_START {12};

/**
 * Initializes the shaders, blocks and their positions, as well as the 
 * vertex buffer data.
 */
Renderer::Renderer() noexcept : 
cubeShader {"shaders/block/blockvertexshader.vert", "shaders/block/blockfragmentshader.frag"}
{
    #if 1
    for (std::int32_t x {}; x < CHUNKS_ON_START; ++x)
        for (std::int32_t z {}; z < CHUNKS_ON_START; ++z)
            allChunks[{x, 0, z}].initChunk({x, 0, z});
    #else
        allChunks[{0, 0, 0}].initChunk({0, 0, 0});
    #endif
    cubeShader.useShader(); 
    cubeShader.setInt("allTextures", 0);

    // Update the visibility of the starting chunks relative to each other.
    // Note that it is fine to simply check if the coordinate is over 0, since
    // all the initialized chunks at the start do not have any negative coordinates.
    for (const auto&[chunkPos, chunk]: allChunks)
    {
        if (chunkPos.x > 0)
        {
            const Chunk* const chunkX {&allChunks.at({chunkPos.x - 1, chunkPos.y, chunkPos.z})};
            chunk.updateChunkVisibilityToNeighbor(chunkX->getChunk(), LeftFace);
            chunkX->updateChunkVisibilityToNeighbor(chunk.getChunk(), RightFace);
        } 
        if (chunkPos.y > 0)
        {
            const Chunk* const chunkY {&allChunks.at({chunkPos.x, chunkPos.y - 1, chunkPos.z})};
            chunk.updateChunkVisibilityToNeighbor(chunkY->getChunk(), BottomFace);
            chunkY->updateChunkVisibilityToNeighbor(chunk.getChunk(), TopFace);
        }
        if (chunkPos.z > 0)
        {
            const Chunk* const chunkZ {&allChunks.at({chunkPos.x, chunkPos.y, chunkPos.z - 1})};
            chunk.updateChunkVisibilityToNeighbor(chunkZ->getChunk(), BackFace);
            chunkZ->updateChunkVisibilityToNeighbor(chunk.getChunk(), FrontFace);
        } 
    }
}

/**
 * Updates the chunks visibility adjacent to
 * the one located at the key given.
 */
void Renderer::updateAdjacentChunks(const std::array<std::array<std::array<Block, CHUNK_LENGTH>, CHUNK_HEIGHT>, CHUNK_WIDTH> &chosenChunk,
                                    const glm::i32vec3 &key) const noexcept
{
    if (allChunks.find({key.x - 1, key.y, key.z}) != allChunks.end())
        allChunks.at({key.x - 1, key.y, key.z}).updateChunkVisibilityToNeighbor(chosenChunk, RightFace);

    if (allChunks.find({key.x + 1, key.y, key.z}) != allChunks.end())
        allChunks.at({key.x + 1, key.y, key.z}).updateChunkVisibilityToNeighbor(chosenChunk, LeftFace);

    if (allChunks.find({key.x, key.y - 1, key.z}) != allChunks.end())
        allChunks.at({key.x, key.y - 1, key.z}).updateChunkVisibilityToNeighbor(chosenChunk, TopFace);

    if (allChunks.find({key.x, key.y + 1, key.z}) != allChunks.end())
        allChunks.at({key.x, key.y + 1, key.z}).updateChunkVisibilityToNeighbor(chosenChunk, BottomFace);

    if (allChunks.find({key.x, key.y, key.z - 1}) != allChunks.end())
        allChunks.at({key.x, key.y, key.z - 1}).updateChunkVisibilityToNeighbor(chosenChunk, FrontFace);

    if (allChunks.find({key.x, key.y, key.z + 1}) != allChunks.end())
        allChunks.at({key.x, key.y, key.z + 1}).updateChunkVisibilityToNeighbor(chosenChunk, BackFace);
}

/**
 * Updates the state of the renderer.
 */
void Renderer::update() noexcept
{
    const auto globalPos {Camera::getCameraPosChunkOffset()};
    if (allChunks.find(globalPos) != allChunks.end())
    {
        Chunk * const activeChunk {&allChunks.at(globalPos)};
        const bool updateNearChunks {activeChunk->updateChunk()};

        if (updateNearChunks)
            updateAdjacentChunks(activeChunk->getChunk(), globalPos);
    }
}

/**
 * Draws all of the chunks.
 */
void Renderer::draw() const noexcept 
{
    // Number of how many chunks the player can see on X and Z
    #if 1
    static constexpr int RENDER_DISTANCE_X {6}, RENDER_DISTANCE_Z {6};
    const auto globalPos {Camera::getCameraPosChunkOffset()};
    for (std::int32_t x {globalPos.x - RENDER_DISTANCE_X}; x < globalPos.x + RENDER_DISTANCE_X; ++x)
    {
        for (std::int32_t z {globalPos.z - RENDER_DISTANCE_Z}; z < globalPos.z + RENDER_DISTANCE_Z; ++z)
        {
            const glm::i32vec3 index {x, 0, z};
            // If the chunk key is found and the player is facing the chunk
            #if 1
            if (allChunks.find(index) != allChunks.end() && Chunk::isFacingChunk(Chunk::getChunkGlobalOffset(index))) 
                allChunks.at(index).drawChunk();
            #else
            if (allChunks.find(index) != allChunks.end())
            {
                if (Chunk::isFacingChunk(Chunk::getChunkGlobalOffset(index)))
                    allChunks.at(index).drawChunk();
                else
                    printf("Chunk {%d, %d, %d} not visible\n", index.x, index.y, index.z);
            }
            #endif
        }
    }
    #else
        #if 0
        for (const auto&[chunkPos, chunk]: allChunks)
        {
            printf("{%lu, %lu, %lu}\n", chunkPos.x, chunkPos.y, chunkPos.z);
            chunk.drawChunk();
        }
        #else
        if (allChunks.find({0, 0, 0}) != allChunks.end())
            allChunks.at({0, 0, 0}).drawChunk();
        #endif
    #endif
}
