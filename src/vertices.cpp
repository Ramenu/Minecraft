#include "minecraft/vertices.hpp"
#include "minecraft/gfx/texture.hpp"

using namespace Texture;

constexpr float xPos_2 {(atlasWidth - 1) * xPos};


// For future reference to the y coordinates, just adjust them inside the vertex shader
// using the .y attribute
constexpr float cubeVertices[288] =
{
   // Position          Texture coordinates     Normal direction (Light)

   // Back (First square)
   -0.5f, -0.5f, 0.0f,    0.0f,      yPos,       0.0f, 0.0f,  1.0f,
    0.0f,  0.5f, 0.0f,    xPos,      0.0f,       0.0f, 0.0f,  1.0f,
    0.0f, -0.5f, 0.0f,    xPos,      yPos,       0.0f, 0.0f,  1.0f,
    0.0f,  0.5f, 0.0f,    xPos,      0.0f,       0.0f, 0.0f,  1.0f,
   -0.5f, -0.5f, 0.0f,    0.0f,      yPos,       0.0f, 0.0f,  1.0f,
   -0.5f,  0.5f, 0.0f,    0.0f,      0.0f,       0.0f, 0.0f,  1.0f,

    // Front (Second square)
   -0.5f, -0.5f, 0.5f,    0.0f,      yPos,       0.0f, 0.0f,  1.0f,
    0.0f, -0.5f, 0.5f,    xPos,      yPos,       0.0f, 0.0f,  1.0f,
    0.0f,  0.5f, 0.5f,    xPos,      0.0f,       0.0f, 0.0f,  1.0f,
    0.0f,  0.5f, 0.5f,    xPos,      0.0f,       0.0f, 0.0f,  1.0f,
   -0.5f,  0.5f, 0.5f,    0.0f,      0.0f,       0.0f, 0.0f,  1.0f,
   -0.5f, -0.5f, 0.5f,    0.0f,      yPos,       0.0f, 0.0f,  1.0f,

    // Right (Third square)
    0.0f,  0.5f, 0.0f,    xPos,      0.0f,       1.0f, 0.0f,  0.0f,
    0.0f, -0.5f, 0.5f,    0.0f,      yPos,       1.0f, 0.0f,  0.0f,
    0.0f, -0.5f, 0.0f,    xPos,      yPos,       1.0f, 0.0f,  0.0f,
    0.0f, -0.5f, 0.5f,    0.0f,      yPos,       1.0f, 0.0f,  0.0f,
    0.0f,  0.5f, 0.0f,    xPos,      0.0f,       1.0f, 0.0f,  0.0f,
    0.0f,  0.5f, 0.5f,    0.0f,      0.0f,       1.0f, 0.0f,  0.0f,
 
    // Left (Fourth square)
   -0.5f,  0.5f, 0.0f,	  xPos,      0.0f,       1.0f, 0.0f,  0.0f,
   -0.5f, -0.5f, 0.0f,    xPos,      yPos,       1.0f, 0.0f,  0.0f,   
   -0.5f, -0.5f, 0.5f,	  0.0f,      yPos,       1.0f, 0.0f,  0.0f,  
   -0.5f, -0.5f, 0.5f,	  0.0f,      yPos,       1.0f, 0.0f,  0.0f,  
   -0.5f,  0.5f, 0.5f,	  0.0f,      0.0f,       1.0f, 0.0f,  0.0f, 
   -0.5f,  0.5f, 0.0f,	  xPos,      0.0f,       1.0f, 0.0f,  0.0f,

    // Up (fifth square)
   -0.5f,  0.5f, 0.5f,    xPos,      yPos,       0.0f,  1.0f, 0.0f, 
   -0.5f,  0.5f, 0.0f,    xPos,      0.0f,       0.0f,  1.0f, 0.0f,
    0.0f,  0.5f, 0.5f,    xPos_2,    yPos,       0.0f,  1.0f, 0.0f,
    0.0f,  0.5f, 0.5f,    xPos_2,    yPos,       0.0f,  1.0f, 0.0f,
   -0.5f,  0.5f, 0.0f,    xPos,      0.0f,       0.0f,  1.0f, 0.0f,
    0.0f,  0.5f, 0.0f,    xPos_2,    0.0f,       0.0f,  1.0f, 0.0f,

    // Bottom (sixth square)
   -0.5f, -0.5f, 0.5f,    xPos_2,    yPos,       0.0f, -1.0f, 0.0f,   
   -0.5f, -0.5f, 0.0f,    xPos_2,    0.0f,       0.0f, -1.0f, 0.0f,
    0.0f, -0.5f, 0.5f,    1.0f,      yPos,       0.0f, -1.0f, 0.0f,                  
    0.0f, -0.5f, 0.5f,    1.0f,      yPos,       0.0f, -1.0f, 0.0f,                  
   -0.5f, -0.5f, 0.0f,    xPos_2,    0.0f,       0.0f, -1.0f, 0.0f,               
    0.0f, -0.5f, 0.0f,    xPos_2,    0.0f,       0.0f, -1.0f, 0.0f              
};
