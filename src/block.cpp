#include "minecraft/block/block.hpp"
#include "minecraft/audio/sound.hpp"
#include "minecraft/gfx/texture.hpp"

/**
 * Initializes the block's Y
 * coordinates in the texture atlas.
 */
void Block::initBlockTextureCoordinates(BlockName block)
{
    switch (block)
    {
        case BlockName::Grass_Block: 
        {
            textureY = 0.0f;
            break;
        }
        case BlockName::Cobblestone_Block: 
        {
            textureY = 1.0f / Texture::atlasHeight;
            break;
        }
    }
}

/**
 * Creates a block with the given name, loading its corresponding subtexture and initializing the block sounds. 
 */
Block::Block(BlockName block, bool withSFX) : name {block}
{
    initBlockTextureCoordinates(name);
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


Block::Block(BlockName block, const glm::vec3 &blockPos) :
name {block},
position {blockPos}
{
    initBlockTextureCoordinates(block);

}


