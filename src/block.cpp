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
    blockMaterial.ambient = glm::vec3{1.0f, 0.5f, 0.31f};
    blockMaterial.specular = glm::vec3{0.5f, 0.5f, 0.5f};
    blockMaterial.shine = 32.0f;
    blockMaterial.diffuse = 0;
}




/* Draws this block. */
void Block::drawBlock() const
{ 
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
