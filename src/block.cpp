#include "minecraft/block/block.hpp"
#include "minecraft/audio/sound.hpp"
#include "minecraft/gfx/texture.hpp"

/**
 * Initializes the block's Y
 * coordinates in the texture atlas.
 */
float Block::initBlockTextureCoordinates(BlockName block) const noexcept
{
    switch (block)
    {
        case BlockName::Grass_Block: return 0.0f;
        case BlockName::Cobblestone_Block: return (1.0f / Texture::atlasHeight);
    }
    exit(EXIT_FAILURE);
}

/**
 * Creates a block with the given name, loading its corresponding subtexture and initializing the block sounds. 
 */
Block::Block(BlockName block, bool withSFX) : 
name {block}, 
textureY {initBlockTextureCoordinates(name)}
{
    if (withSFX)
        playBlockPlacementSound(name);
}


/**
 * Plays the block's sound on destruction.
 * Typically played when the player 
 * destroys a block. Not when the block's
 * destructor is being called!
 */
void Block::playDestroyedSound() const
{
    playBlockBreakSound(name);
}

/**
 * Constructs a block at the given position.
 * Does not play SFX.
 */
Block::Block(BlockName block, const glm::vec3 &blockPos) :
position {blockPos},
name {block},
textureY {initBlockTextureCoordinates(block)}
{}


