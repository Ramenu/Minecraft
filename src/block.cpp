#include "minecraft/block/block.hpp"
#include "minecraft/audio/sound.hpp"
#include "minecraft/gfx/texture.hpp"
#include "glad/glad.h"


/* Creates a block with the given name, loading its corresponding subtexture and initializing the block sounds. */
Block::Block(BlockName block, bool withSFX) : name {block}
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
    if (withSFX)
        playBlockPlacementSound(name);
}

/* Draws this block. */
void Block::draw() const
{
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Block::playDestroyedSound() const
{
    playBlockBreakSound(name);
}



