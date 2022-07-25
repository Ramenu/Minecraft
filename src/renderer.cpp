#include "minecraft/rendering/renderer.hpp"
#include "minecraft/block/face.h"
#include "minecraft/math/glmath.hpp"
#include "minecraft/rendering/renderinfo.hpp"
#include "minecraft/world/chunkgenerator.hpp"
#include <cstdio>


/**
 * Initializes the shaders, blocks and their positions, as well as the 
 * vertex buffer data.
 */
Renderer::Renderer() noexcept : 
cubeShader {"shaders/block/blockvertexshader.vert", "shaders/block/blockfragmentshader.frag"}
{
    const glm::i32vec3 p {Camera::getCameraPosChunkOffset()};
    for (auto x {p.x - RENDER_DISTANCE_X}; x < p.x + RENDER_DISTANCE_X; ++x)
        for (auto z {p.z - RENDER_DISTANCE_Z}; z < p.z + RENDER_DISTANCE_Z; ++z)
            allChunks[{x, 0, z}].initChunk({x, 0, z});
    cubeShader.useShader(); 
    cubeShader.setInt("allTextures", 0);

    for (const auto&[chunkPos, chunk]: allChunks)
        updateAdjacentChunks(chunk, chunkPos);
}

/**
 * Updates the chunks visibility adjacent to
 * the one located at the key given.
 */
void Renderer::updateAdjacentChunks(const Chunk &chunk, const glm::i32vec3 &key) const noexcept
{
    if (allChunks.find({key.x - 1, key.y, key.z}) != allChunks.end())
    {
        const Chunk* const chunkLeftX {&allChunks.at({key.x - 1, key.y, key.z})};
        chunkLeftX->updateChunkVisibilityToNeighbor(chunk.getChunk(), RightFace);
        chunk.updateChunkVisibilityToNeighbor(chunkLeftX->getChunk(), LeftFace);
    }

    if (allChunks.find({key.x + 1, key.y, key.z}) != allChunks.end())
    {
        const Chunk* const chunkPosX {&allChunks.at({key.x + 1, key.y, key.z})};
        chunkPosX->updateChunkVisibilityToNeighbor(chunk.getChunk(), LeftFace);
        chunk.updateChunkVisibilityToNeighbor(chunkPosX->getChunk(), RightFace);
    }

    // Top and bottom chunks not a feature (yet..)
    #if 0
    if (allChunks.find({key.x, key.y - 1, key.z}) != allChunks.end())
        allChunks.at({key.x, key.y - 1, key.z}).updateChunkVisibilityToNeighbor(chunk.getChunk(), TopFace);

    if (allChunks.find({key.x, key.y + 1, key.z}) != allChunks.end())
        allChunks.at({key.x, key.y + 1, key.z}).updateChunkVisibilityToNeighbor(chunk.getChunk(), BottomFace);
    #endif

    if (allChunks.find({key.x, key.y, key.z - 1}) != allChunks.end())
    {
        const Chunk* const chunkPosZ {&allChunks.at({key.x, key.y, key.z - 1})};
        chunkPosZ->updateChunkVisibilityToNeighbor(chunk.getChunk(), FrontFace);
        chunk.updateChunkVisibilityToNeighbor(chunkPosZ->getChunk(), BackFace);
    }

    if (allChunks.find({key.x, key.y, key.z + 1}) != allChunks.end())
    {
        const Chunk* const chunkNegZ {&allChunks.at({key.x, key.y, key.z + 1})};
        chunkNegZ->updateChunkVisibilityToNeighbor(chunk.getChunk(), BackFace);
        chunk.updateChunkVisibilityToNeighbor(chunkNegZ->getChunk(), FrontFace);
    }
}

/**
 * Removes the chunks that are 'far away' from
 * the camera. This is done so the program doesn't build
 * up memory overtime.
 */
void Renderer::removeFarawayChunks(const glm::i32vec3 &globalPos) noexcept 
{
    std::int32_t farZ {globalPos.z - RENDER_DISTANCE_Z - PRELOAD_CHUNKS - 1};
    std::int32_t farX {globalPos.x - RENDER_DISTANCE_X - PRELOAD_CHUNKS - 1};
    for (int i {}; i < 2; ++i)
    {
        for (std::int32_t x {globalPos.x - RENDER_DISTANCE_X - PRELOAD_CHUNKS - 1}; x < globalPos.x + RENDER_DISTANCE_X + PRELOAD_CHUNKS + 1; ++x)
        {
            if (allChunks.find({x, 0, farZ}) != allChunks.end())
            {
                Chunk * const chunk {&allChunks.at({x, 0, farZ})};
                const ChunkTerrain terrain {.chunk = chunk->getChunk(), .topLayer = chunk->getTopLayer(), .lowestLayer = chunk->getBottomLayer()};
                ChunkGenerator::updateChunkAt(terrain, {x, 0, farZ});
                allChunks.erase({x, 0, farZ});
            }
        }
        farZ = globalPos.z + RENDER_DISTANCE_Z + PRELOAD_CHUNKS + 1;
    }

    for (int i {}; i < 2; ++i)
    {
        for (std::int32_t z {globalPos.z - RENDER_DISTANCE_Z - PRELOAD_CHUNKS - 1}; z < globalPos.z + RENDER_DISTANCE_Z + PRELOAD_CHUNKS + 1; ++z)
        {
            if (allChunks.find({farX, 0, z}) != allChunks.end())
            {
                Chunk * const chunk {&allChunks.at({farX, 0, z})};
                const ChunkTerrain terrain {.chunk = chunk->getChunk(), .topLayer = chunk->getTopLayer(), .lowestLayer = chunk->getBottomLayer()};
                ChunkGenerator::updateChunkAt(terrain, {farX, 0, z});
                allChunks.erase({farX, 0, z});
            }
        }
        farX = globalPos.x + RENDER_DISTANCE_X + PRELOAD_CHUNKS + 1;
    }

}


/**
 * Updates the state of the renderer.
 */
void Renderer::update() noexcept
{
    static auto lastPos {Camera::getCameraPosChunkOffset()};
    const auto globalPos {Camera::getCameraPosChunkOffset()};

    // We need to check if the chunk offset changed since the last call, since
    // the last chunk may have an invalid state (e.g., block still highlighted).
    // If this is the case, then we need to update the last chunk the camera was on.
    if (lastPos.x != globalPos.x || lastPos.z != globalPos.z)
    {
        if (allChunks.find({lastPos.x, 0, lastPos.z}) != allChunks.end())
        {
            allChunks[lastPos].updateChunk();
            lastPos = globalPos;
        }
    }

    if (allChunks.find(globalPos) != allChunks.end())
    {
        Chunk * const activeChunk {&allChunks[globalPos]};
        const bool updateNearChunks {activeChunk->updateChunk()};

        if (updateNearChunks)
            updateAdjacentChunks(*activeChunk, globalPos);
    }
}

/**
 * Creates a chunk at the given location and draws it.
 */
void Renderer::createChunk(const glm::i32vec3 &chunkPos) noexcept 
{
    Chunk * const chunk {&allChunks[chunkPos]};
    chunk->initChunk(chunkPos);
    updateAdjacentChunks(*chunk, chunkPos);
}

/**
 * Draws all of the chunks.
 */
void Renderer::draw() noexcept 
{
    const auto globalPos {Camera::getCameraPosChunkOffset()};
    static constexpr unsigned int CALL_COUNT_RESET {6}; // Change this number if you want chunks to render faster or slower
    static unsigned int callCount {};
    ++callCount;
    bool createdChunkThisFrame {false};

    for (std::int32_t x {globalPos.x - RENDER_DISTANCE_X}; x < globalPos.x + RENDER_DISTANCE_X; ++x)
    {
        for (std::int32_t z {globalPos.z - RENDER_DISTANCE_Z}; z < globalPos.z + RENDER_DISTANCE_Z; ++z)
        {
            const glm::i32vec3 index {x, 0, z};
            // If the chunk key is found and the player is facing the chunk
            if (Chunk::isFacingChunk(Chunk::getChunkGlobalOffset(index)))
            {
                if (allChunks.find(index) != allChunks.end()) 
                {
                    if (Chunk::isFacingChunk(Chunk::getChunkGlobalOffset(index)))
                        allChunks.at(index).drawChunk();
                }
                else if (callCount % CALL_COUNT_RESET == 0 && !createdChunkThisFrame)
                {
                    createChunk(index);
                    createdChunkThisFrame = true;
                }
            }
            
        }
    }
    removeFarawayChunks(globalPos);
}
