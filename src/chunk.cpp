#include "minecraft/rendering/chunk.hpp"
#include <cmath>
#include <cstdio>

/**
 * Returns the block's position in the 
 * layout of the vertex buffer.
 */
static inline size_t getBlockIndex(uint8_t x, int8_t y, uint8_t z) 
{
    return x * chunkLength * chunkHeight + ((-y - 1) * chunkLength + z);
}


/**
 * Modifies the chunk's block located
 * at {x, y, z}. Parameters include:
 * -> position of the block (x, y, z) must be three whole numbers
 * -> textureID of the block 
 * -> An array of 6 floats which specify which faces should be visible
 */
void Chunk::modifyChunk(uint8_t x, uint8_t y, uint8_t z,
                        Block block,
                        const std::array<float, noOfSquaresInCube> &visible) noexcept 
{
    chunk[x][y][z] = block;
    constexpr auto defaultTextureVertices {getTextureVertices(0.0f)};
    const size_t block3DIndex {getBlockIndex(x, y, z)};

    const size_t texOffset {block3DIndex * textureVerticesSize};
    const size_t visibleOffset {block3DIndex * visibleVerticesSize};

    // Start from texOffset + 1 so we can start from y coordinate (changes the block's texture)
    for (size_t i {texOffset + 1}; i < texOffset + textureVerticesSize; i += 2)
        chunkVertices.texture[i] = defaultTextureVertices[i - texOffset] + block.getTexture();
    
    // Apply the visibility changes to each of the block's faces
    chunkVertices.visibility[visibleOffset] = visible[0];
    chunkVertices.visibility[visibleOffset + 1] = visible[0];
    chunkVertices.visibility[visibleOffset + 2] = visible[0];
    chunkVertices.visibility[visibleOffset + 3] = visible[0];
    chunkVertices.visibility[visibleOffset + 4] = visible[0];
    chunkVertices.visibility[visibleOffset + 5] = visible[0];

    chunkVertices.visibility[visibleOffset + 6] = visible[1];
    chunkVertices.visibility[visibleOffset + 7] = visible[1];
    chunkVertices.visibility[visibleOffset + 8] = visible[1];
    chunkVertices.visibility[visibleOffset + 9] = visible[1];
    chunkVertices.visibility[visibleOffset + 10] = visible[1];
    chunkVertices.visibility[visibleOffset + 11] = visible[1];

    chunkVertices.visibility[visibleOffset + 12] = visible[2];
    chunkVertices.visibility[visibleOffset + 13] = visible[2];
    chunkVertices.visibility[visibleOffset + 14] = visible[2];
    chunkVertices.visibility[visibleOffset + 15] = visible[2];
    chunkVertices.visibility[visibleOffset + 16] = visible[2];
    chunkVertices.visibility[visibleOffset + 17] = visible[2];

    chunkVertices.visibility[visibleOffset + 18] = visible[3];
    chunkVertices.visibility[visibleOffset + 19] = visible[3];
    chunkVertices.visibility[visibleOffset + 20] = visible[3];
    chunkVertices.visibility[visibleOffset + 21] = visible[3];
    chunkVertices.visibility[visibleOffset + 22] = visible[3];
    chunkVertices.visibility[visibleOffset + 23] = visible[3];

    chunkVertices.visibility[visibleOffset + 24] = visible[4];
    chunkVertices.visibility[visibleOffset + 25] = visible[4];
    chunkVertices.visibility[visibleOffset + 26] = visible[4];
    chunkVertices.visibility[visibleOffset + 27] = visible[4];
    chunkVertices.visibility[visibleOffset + 28] = visible[4];
    chunkVertices.visibility[visibleOffset + 29] = visible[4];

    chunkVertices.visibility[visibleOffset + 30] = visible[5];
    chunkVertices.visibility[visibleOffset + 31] = visible[5];
    chunkVertices.visibility[visibleOffset + 32] = visible[5];
    chunkVertices.visibility[visibleOffset + 33] = visible[5];
    chunkVertices.visibility[visibleOffset + 34] = visible[5];
    chunkVertices.visibility[visibleOffset + 35] = visible[5];
}

bool Chunk::blockIsVisibleToPlayer(const glm::vec3 &block3DIndex) const noexcept 
{
    // This means that it is on the outskirts of the chunk, which means it is visible to the player
    if (isOutOfChunk(block3DIndex + 1.0f) || isOutOfChunk(block3DIndex - 1.0f))
        return true; 

    assert((chunk[block3DIndex.x + 1][block3DIndex.y][block3DIndex.z].name == BlockName::Air_Block ||
             chunk[block3DIndex.x - 1][block3DIndex.y][block3DIndex.z].name == BlockName::Air_Block ||
             chunk[block3DIndex.x][block3DIndex.y + 1][block3DIndex.z].name == BlockName::Air_Block ||
             chunk[block3DIndex.x][block3DIndex.y - 1][block3DIndex.z].name == BlockName::Air_Block ||
             chunk[block3DIndex.x][block3DIndex.y][block3DIndex.z + 1].name == BlockName::Air_Block ||
             chunk[block3DIndex.x][block3DIndex.y][block3DIndex.z - 1].name == BlockName::Air_Block) == false);
    // Check each block next to this block, if all of them are not air blocks then it is not visible to the player
    return  (chunk[block3DIndex.x + 1][block3DIndex.y][block3DIndex.z].name == BlockName::Air_Block ||
             chunk[block3DIndex.x - 1][block3DIndex.y][block3DIndex.z].name == BlockName::Air_Block ||
             chunk[block3DIndex.x][block3DIndex.y + 1][block3DIndex.z].name == BlockName::Air_Block ||
             chunk[block3DIndex.x][block3DIndex.y - 1][block3DIndex.z].name == BlockName::Air_Block ||
             chunk[block3DIndex.x][block3DIndex.y][block3DIndex.z + 1].name == BlockName::Air_Block ||
             chunk[block3DIndex.x][block3DIndex.y][block3DIndex.z - 1].name == BlockName::Air_Block);
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
    for (uint8_t x {}; x < chunkWidth; x++)
    {
        for (uint8_t y {}; y < chunkHeight; y++)
        {
            for (uint8_t z {}; z < chunkLength; z++)
            {
                const auto visible {(blockIsVisibleToPlayer({x, y, z})) ? 
                                    getVisibleBlockVertices({1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f}) :
                                    getVisibleBlockVertices({0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f})};
                chunkVertices.visibility.insert(chunkVertices.visibility.end(),
                                                std::begin(visible),
                                                std::end(visible));
            }
        }
    }
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
    constexpr uint8_t halfOfWidth {chunkWidth / 2}, halfOfLength {chunkLength / 2};
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
