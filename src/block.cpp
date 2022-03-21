#include "minecraft/block/block.hpp"
#include "minecraft/audio/sound.hpp"
#include "minecraft/gfx/texture.hpp"

/**
 * Initializes the block's Y
 * coordinates in the texture atlas.
 */
float Block::initBlockTextureCoordinates(BlockName block) noexcept
{
    switch (block)
    {
        case BlockName::Grass_Block: 
            id = BlockSoundID::Grass_Block;
            return 0.0f;
        case BlockName::Cobblestone_Block: 
            id = BlockSoundID::Stone_Block;
            return (1.0f / Texture::atlasHeight);
    }
    exit(EXIT_FAILURE);
}

/**
 * Creates a block with the given name, loading its corresponding subtexture and initializing the block sounds. 
 */
Block::Block(BlockName block, bool withSFX) noexcept : 
textureY {initBlockTextureCoordinates(block)}
{
    if (withSFX)
        Sound::playBlockPlacementSound(id);
}



/**
 * Constructs a block at the given position.
 * Does not play SFX.
 */
Block::Block(BlockName block, bool withSFX, const glm::vec3 &blockPos) noexcept :
position {blockPos},
textureY {initBlockTextureCoordinates(block)}
{
    if (withSFX)
        Sound::playBlockPlacementSound(id);
}




