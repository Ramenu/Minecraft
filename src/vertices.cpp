#include "minecraft/vertices.hpp"
#include "minecraft/gfx/texture.hpp"

using namespace Texture;

constexpr float xStrideToNextBlock {atlasWidth - 1};

// For future reference to the y coordinates, just adjust them inside the vertex shader
// using the .y attribute
constexpr float cubeVertices[288] =
{
    //                               First block
    // Position                Texture coordinates                  Normal direction
   -0.5f, -0.5f, 0.0f,    0.0f,                      yPos,         0.0f, 0.0f,  1.0f,
   -0.5f,  0.5f, 0.0f,    0.0f,                      0.0f,         0.0f, 0.0f,  1.0f,
    0.0f, -0.5f, 0.0f,    xPos,                      yPos,         0.0f, 0.0f,  1.0f,
    0.0f, -0.5f, 0.0f,    xPos,                      yPos,         0.0f, 0.0f,  1.0f,
   -0.5f,  0.5f, 0.0f,    0.0f,                      0.0f,         0.0f, 0.0f,  1.0f,
    0.0f,  0.5f, 0.0f,    xPos,                      0.0f,         0.0f, 0.0f,  1.0f,

   -0.5f, -0.5f, 0.5f,    0.0f,                      yPos,         0.0f, 0.0f,  1.0f,
   -0.5f,  0.5f, 0.5f,    0.0f,                      0.0f,         0.0f, 0.0f,  1.0f,
    0.0f, -0.5f, 0.5f,    xPos,                      yPos,         0.0f, 0.0f,  1.0f,
    0.0f, -0.5f, 0.5f,    xPos,                      yPos,         0.0f, 0.0f,  1.0f,
   -0.5f,  0.5f, 0.5f,    0.0f,                      0.0f,         0.0f, 0.0f,  1.0f,
    0.0f,  0.5f, 0.5f,    xPos,                      0.0f,         0.0f, 0.0f,  1.0f,

   -0.5f, -0.5f, 0.5f,	  0.0f,                      yPos,         1.0f, 0.0f,  0.0f,  
   -0.5f,  0.5f, 0.5f,	  0.0f,                      0.0f,         1.0f, 0.0f,  0.0f, 
   -0.5f, -0.5f, 0.0f,    xPos,                      yPos,         1.0f, 0.0f,  0.0f,   
   -0.5f, -0.5f, 0.0f,	  xPos,                      yPos,         1.0f, 0.0f,  0.0f,  
   -0.5f,  0.5f, 0.5f,	  0.0f,                      0.0f,         1.0f, 0.0f,  0.0f,  
   -0.5f,  0.5f, 0.0f,	  xPos,                      0.0f,         1.0f, 0.0f,  0.0f,

    0.0f, -0.5f, 0.5f,    0.0f,                      yPos,         1.0f, 0.0f, 0.0f,
    0.0f,  0.5f, 0.5f,    0.0f,                      0.0f,         1.0f, 0.0f, 0.0f,
    0.0f, -0.5f, 0.0f,    xPos,                      yPos,         1.0f, 0.0f, 0.0f,
    0.0f, -0.5f, 0.0f,    xPos,                      yPos,         1.0f, 0.0f, 0.0f,
    0.0f,  0.5f, 0.5f,    0.0f,                      0.0f,         1.0f, 0.0f, 0.0f,
    0.0f,  0.5f, 0.0f,    xPos,                      0.0f,         1.0f, 0.0f, 0.0f,

    //                            Second block
   -0.5f,  0.5f, 0.5f,    xPos,                      yPos,         0.0f,  1.0f, 0.0f, 
   -0.5f,  0.5f, 0.0f,    xPos,                      0.0f,         0.0f,  1.0f, 0.0f,
    0.0f,  0.5f, 0.5f,    xPos * xStrideToNextBlock, yPos,         0.0f,  1.0f, 0.0f,
    0.0f,  0.5f, 0.5f,    xPos * xStrideToNextBlock, yPos,         0.0f,  1.0f, 0.0f,
   -0.5f,  0.5f, 0.0f,    xPos,                      0.0f,         0.0f,  1.0f, 0.0f,
    0.0f,  0.5f, 0.0f,    xPos * xStrideToNextBlock, 0.0f,         0.0f,  1.0f, 0.0f,

    //                            Third block
   -0.5f, -0.5f, 0.5f,    xPos * xStrideToNextBlock, yPos,         0.0f, -1.0f, 0.0f,   
   -0.5f, -0.5f, 0.0f,    xPos * xStrideToNextBlock, 0.0f,         0.0f, -1.0f, 0.0f,
    0.0f, -0.5f, 0.5f,    xPos * atlasWidth,         yPos,         0.0f, -1.0f, 0.0f,                  
    0.0f, -0.5f, 0.5f,    xPos * atlasWidth,         yPos,         0.0f, -1.0f, 0.0f,                  
   -0.5f, -0.5f, 0.0f,    xPos * xStrideToNextBlock, 0.0f,         0.0f, -1.0f, 0.0f,               
    0.0f, -0.5f, 0.0f,    xPos * xStrideToNextBlock, 0.0f,         0.0f, -1.0f, 0.0f,               
};
