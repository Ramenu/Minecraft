#include "mylib/block.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include "mylib/graphics/textures.hpp"

unsigned int Block::blockID {};

/* Constructor for Block, initializes the textures and the total number of textures the block has.*/
Block::Block(const char* pathToDirectory) : blockTextures {}, noOfTextures {}, upTo {36}
{
    namespace fs = std::filesystem;
    blockID++;
    // Iterate through the directory
    for (const auto&entry: fs::directory_iterator(pathToDirectory))
    {
        if (entry.path().extension() == ".jpg")
        {
            /* It is important to assign the right textures to the proper indices in the array, so that when the blocks are drawn
               the textures will be on the correct faces of the block. */
            if (entry.path().string().find("wrapper") != std::string::npos)
            {
                glGenTextures(1, &blockTextures[0]);
                glBindTexture(GL_TEXTURE_2D, blockTextures[0]);
                //glActiveTexture(0);
                createTexture(entry.path().string().c_str(), GL_REPEAT, blockTextures[0]);
            }
            else if (entry.path().string().find("top") != std::string::npos)
            {
                glGenTextures(1, &blockTextures[1]);
                glBindTexture(GL_TEXTURE_2D, blockTextures[1]);
                //glActiveTexture(1);
                createTexture(entry.path().string().c_str(), GL_REPEAT, blockTextures[1]);
                noOfTextures++;
                upTo -= 6;
            }
            else
            {
                glGenTextures(1, &blockTextures[2]);
                glBindTexture(GL_TEXTURE_2D, blockTextures[2]);
                //glActiveTexture(2);
                createTexture(entry.path().string().c_str(), GL_REPEAT, blockTextures[2]);
                noOfTextures++;
                upTo -= 6;
            }
        }
        if (noOfTextures == 3) break; // Only a maximum of 3 textures is allowed
    }
}


/* Class destructor for Block. */
Block::~Block()
{
    for (unsigned short i {}; i < noOfTextures; i++)
        glDeleteTextures(1, &blockTextures[i]);
}

/* Draws this block on the x, y, z coordinates passed. */
void Block::drawBlock()
{

    unsigned short startAtIndice {}, max {upTo};
    for (unsigned short i {}; i < 3; i++)
    {
        glBindTexture(GL_TEXTURE_2D, blockTextures[i]);
        glDrawArrays(GL_TRIANGLES, startAtIndice, max);
        startAtIndice = i * 6 + 24;
        max = 6;
    }
}