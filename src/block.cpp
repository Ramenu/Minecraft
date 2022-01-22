#include "mylib/block.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


/* Constructor for Block, initializes the textures and the total number of textures the block has. */
Block::Block(SubTextures subTexture)
{
    typedef SubTextures T;
    switch (subTexture)
    {
        case T::GRASS_BLOCK: blockTexture = SubTexture(0, 0); break;
        case T::COBBLESTONE_BLOCK: blockTexture = SubTexture(1, 1); break;
    }
}


/* Class destructor for Block. */
Block::~Block()
{

}

/* Draws this block. */
void Block::drawBlock() const
{ 
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
