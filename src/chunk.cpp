#include "minecraft/rendering/renderer.hpp"

/**
 * Returns true if the block located at {x, y, z}
 * is visible to the player (that is, not hidden by other blocks
 * so the player can't see it).
 */
bool Chunk::blockIsVisibleToPlayer(const glm::vec3 &blockIndex) const noexcept 
{
    // This means that it is on the outskirts of the chunk, which means it is visible to the player
    if (isOutOfChunk(blockIndex + 1.0f) || isOutOfChunk(blockIndex - 1.0f))
        return true; 
    
    // Check each block next to this block, if all of them are air blocks then it is not visible to the player
    return  (chunk[blockIndex.x + 1][blockIndex.y][blockIndex.z].name == BlockName::Air_Block ||
             chunk[blockIndex.x - 1][blockIndex.y][blockIndex.z].name == BlockName::Air_Block ||
             chunk[blockIndex.x][blockIndex.y + 1][blockIndex.z].name == BlockName::Air_Block ||
             chunk[blockIndex.x][blockIndex.y - 1][blockIndex.z].name == BlockName::Air_Block ||
             chunk[blockIndex.x][blockIndex.y][blockIndex.z + 1].name == BlockName::Air_Block ||
             chunk[blockIndex.x][blockIndex.y][blockIndex.z - 1].name == BlockName::Air_Block);
}
