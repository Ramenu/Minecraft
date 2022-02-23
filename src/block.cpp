#include "mylib/block/block.hpp"
#include "glad/glad.h"



/* Constructor for Block, initializes the textures and the total number of textures the block has. */
Block::Block(BlockName block)
{
    switch (block)
    {
        case BlockName::Grass_Block: blockTexture = SubTexture{0, 0}; break;
        case BlockName::Cobblestone_Block: blockTexture = SubTexture{1, 1}; break;
    }
}


/* Draws this block. */
void Block::drawBlock() const
{ 
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
