#include "minecraft/block/block.hpp"
#include "minecraft/audio/sound.hpp"
#include "minecraft/gfx/texture.hpp"



/**
 * Creates a block with the given name, loading its corresponding subtexture and initializing the block sounds. 
 */
Block::Block(BlockName block, bool withSFX) noexcept :
name {block} 
{
    if (withSFX)
        Sound::playBlockPlacementSound(block);
}


/**
 * Constructs a block at the given position.
 * Does not play SFX.
 */
Block::Block(BlockName block, bool withSFX, const glm::vec3 &blockPos) noexcept :
position {blockPos},
name {block}
{
    if (withSFX)
        Sound::playBlockPlacementSound(name);
}




