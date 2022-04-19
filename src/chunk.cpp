#include "minecraft/rendering/chunk.hpp"
#include "misc/literals.hpp"
#include "minecraft/camera/camera.hpp"
#include "minecraft/math/glmath.hpp"
#include <cmath>
#include <cstdio>

static_assert(chunkHeight == chunkWidth && chunkHeight == chunkLength, "ERROR: Width, height, and length of the chunk must be equal!");

/**
 * Returns the block's position in the 
 * layout of the vertex buffer.
 */
static inline size_t getBlockIndex(ChunkIndex index) noexcept
{
    return index.x * chunkLength * chunkHeight + ((-index.y - 1) * chunkLength + index.z);
}


/**
 * Modifies the chunk's block located
 * at {x, y, z}. Parameters include:
 * -> position of the block (x, y, z) must be three whole numbers
 * -> textureID of the block 
 * -> An array of 6 floats which specify which faces should be visible
 */
void Chunk::modifyChunk(ChunkIndex chunkIndex, Block block) noexcept 
{
    const int8_t x {chunkIndex.x}, y {chunkIndex.y}, z {chunkIndex.z};
    chunk[x][y][z] = block;

    const size_t index {getBlockIndex(chunkIndex)};


    if (block.name != BlockName::Air_Block)
    {
        static constexpr auto defaultTextureVertices {getTextureVertices(0.0f)};

        // Start from texOffset + 1 so we can start from y coordinate (changes the block's texture)
        const size_t texOffset {index * textureVerticesSize};
        for (size_t i {texOffset + 1}; i < texOffset + textureVerticesSize; i += 2)
            chunkVertices.texture[i] = defaultTextureVertices[i - texOffset] + block.getTexture();
    }
    updateChunkVisibility();

}

/**
 * Returns the visible faces of the block in
 * an array of six floats (1.0f = visible, 0.0f = not visible)
 * Checks the neighbor of each block's direction and if it
 * is out of the chunk's border OR is an air block the face
 * will be visible.
 */
std::array<float, noOfSquaresInCube> Chunk::getVisibleFaces(ChunkIndex index) const noexcept 
{
    std::array<float, noOfSquaresInCube> visibleFaces {};

    // Back face
    // NOTE: Accessing outside of array's boundaries could lead to undefined behavior. Fix this
    if (isOutOfChunk({index.x , index.y, static_cast<int8_t>(index.z - 1)}) || 
            chunk[index.x][index.y][index.z - 1].name == BlockName::Air_Block)
                visibleFaces[0] = 1.0f;

    // Front face
    if (isOutOfChunk({index.x , index.y, static_cast<int8_t>(index.z + 1)}) ||
        chunk[index.x][index.y][index.z + 1].name == BlockName::Air_Block)
            visibleFaces[1] = 1.0f;

    // Right face
    if (isOutOfChunk({static_cast<int8_t>(index.x + 1), index.y, index.z}) ||
        chunk[index.x + 1][index.y][index.z].name == BlockName::Air_Block)
            visibleFaces[2] = 1.0f;
    
    // Left face
    if (isOutOfChunk({static_cast<int8_t>(index.x - 1), index.y, index.z}) || 
        chunk[index.x - 1][index.y][index.z].name == BlockName::Air_Block)
            visibleFaces[3] = 1.0f;
    
    // Top face
    if (isOutOfChunk({index.x ,static_cast<int8_t>(index.y + 1), index.z}) ||
        chunk[index.x][index.y + 1][index.z].name == BlockName::Air_Block)
            visibleFaces[4] = 1.0f;

    // Bottom face
    if (isOutOfChunk({index.x ,static_cast<int8_t>(index.y - 1), index.z}) || 
        chunk[index.x][index.y - 1][index.z].name == BlockName::Air_Block)
            visibleFaces[5] = 1.0f;
    
    return visibleFaces;
}

/**
 * Updates the entire chunk's blocks.
 * Checks which blocks are visible to
 * the player. Should be called whenever
 * the chunk's state has changed.
 */
void Chunk::updateChunkVisibility() noexcept 
{
    chunkVertices.visibility.clear();
    for (int8_t x {}; x < chunkWidth; x++)
    {
        for (int8_t y {chunkHeight - 1_i8}; y >= 0; y--)
        {
            for (int8_t z {}; z < chunkLength; z++)
            {
                const ChunkIndex index {ChunkIndex{x, y, z}};
                if (blockIsVisibleToPlayer(index) && chunk[x][y][z].name != BlockName::Air_Block)
                {
                    const auto visible {getVisibleBlockVertices(getVisibleFaces(index))};
                    chunkVertices.visibility.insert(chunkVertices.visibility.end(),
                                                    std::begin(visible),
                                                    std::end(visible));
                    continue;
                }
                const auto visible {getVisibleBlockVertices({0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f})};
                chunkVertices.visibility.insert(chunkVertices.visibility.end(),
                                                visible.begin(),
                                                visible.end());
            }
        }
    }
}


bool Chunk::blockIsVisibleToPlayer(ChunkIndex index) const noexcept 
{
    // This means that it is on the outskirts of the chunk, which means it is visible to the player
    if (isOutOfChunk(index + 1_i8) || isOutOfChunk(index - 1_i8))
    {
        return true; 
    }
    

    // Check each block next to this block, if all of them are not air blocks then it is not visible to the player
    return  (chunk[index.x + 1_i8][index.y][index.z].name == BlockName::Air_Block ||
             chunk[index.x - 1_i8][index.y][index.z].name == BlockName::Air_Block ||
             chunk[index.x][index.y + 1_i8][index.z].name == BlockName::Air_Block ||
             chunk[index.x][index.y - 1_i8][index.z].name == BlockName::Air_Block ||
             chunk[index.x][index.y][index.z + 1_i8].name == BlockName::Air_Block ||
             chunk[index.x][index.y][index.z - 1_i8].name == BlockName::Air_Block);
}


/**
 * Chunk's constructor. Initializes each of the
 * vectors to the same vertices. Though, since this
 * is very expensive chunk construction should be kept
 * to a minimum and be created before the main game
 * loop. If necessary to make a new chunk in the loop,
 * do it in a seperate thread.
 */
Chunk::Chunk(BlockName firstLayer, BlockName bottomLayers) noexcept
{
    static constexpr uint8_t halfOfWidth {chunkWidth / 2}, halfOfLength {chunkLength / 2};
    uint8_t xU {}, yU {}, zU {};
    for (float x {}; x < halfOfWidth; x += 0.5f)
    {
        BlockName selectedBlock {firstLayer};
        for (float y {chunkHeight - 1}; y >= 0; y -= 1.0f)
        {
            for (float z {}; z < halfOfLength; z += 0.5f)
            {
                const Block block {selectedBlock};
                chunk[xU][yU][zU] = block;
                const auto pos {createCubeAt(x, y, z)};
                const auto texture {getTextureVertices(block.getTexture())};
                chunkVertices.position.insert(chunkVertices.position.end(), 
                                            std::begin(pos), 
                                            std::end(pos));
                chunkVertices.texture.insert(chunkVertices.texture.end(),
                                            std::begin(texture),
                                            std::end(texture));
                chunkVertices.lightDirection.insert(chunkVertices.lightDirection.end(),
                                                    std::begin(defaultLightDirectionVertices),
                                                    std::end(defaultLightDirectionVertices));

                zU++;
            }
            selectedBlock = bottomLayers;
            zU = 0;
            yU++;
        }
        yU = 0;
        xU++;
    }
    // We can't update the visibility in the loop prior to this call,
    // because the array's elements do not get initialized until after
    // the loop ends. 
    updateChunkVisibility();
}
