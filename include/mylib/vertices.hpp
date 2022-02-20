#ifndef VERTICES_HPP
#define VERTICES_HPP

#include "mylib/gfx/texture.hpp"

inline constexpr float cubeVertices[288] =
{
   -0.5f, -0.5f, 0.0f,    0.0f, yPos,   0.0f, 0.0f,  1.0f,
   -0.5f,  0.5f, 0.0f,    0.0f, 0.0f,   0.0f, 0.0f,  1.0f,
    0.0f, -0.5f, 0.0f,    xPos, yPos,   0.0f, 0.0f,  1.0f,
    0.0f, -0.5f, 0.0f,    xPos, yPos,   0.0f, 0.0f,  1.0f,
   -0.5f,  0.5f, 0.0f,    0.0f, 0.0f,   0.0f, 0.0f,  1.0f,
    0.0f,  0.5f, 0.0f,    xPos, 0.0f,   0.0f, 0.0f,  1.0f,

   -0.5f, -0.5f, 0.5f,    0.0f, yPos,   0.0f, 0.0f,  1.0f,
   -0.5f,  0.5f, 0.5f,    0.0f, 0.0f,   0.0f, 0.0f,  1.0f,
    0.0f, -0.5f, 0.5f,    xPos, yPos,   0.0f, 0.0f,  1.0f,
    0.0f, -0.5f, 0.5f,    xPos, yPos,   0.0f, 0.0f,  1.0f,
   -0.5f,  0.5f, 0.5f,    0.0f, 0.0f,   0.0f, 0.0f,  1.0f,
    0.0f,  0.5f, 0.5f,    xPos, 0.0f,   0.0f, 0.0f,  1.0f,

   -0.5f, -0.5f, 0.5f,	  0.0f, yPos,   1.0f, 0.0f,  0.0f,  
   -0.5f,  0.5f, 0.5f,	  0.0f, 0.0f,   1.0f, 0.0f,  0.0f, 
   -0.5f, -0.5f, 0.0f,    xPos, yPos,   1.0f, 0.0f,  0.0f,   
   -0.5f, -0.5f, 0.0f,	  xPos, yPos,   1.0f, 0.0f,  0.0f,  
   -0.5f,  0.5f, 0.5f,	  0.0f, 0.0f,   1.0f, 0.0f,  0.0f,  
   -0.5f,  0.5f, 0.0f,	  xPos, 0.0f,   1.0f, 0.0f,  0.0f,

    0.0f, -0.5f, 0.5f,    0.0f, yPos,   1.0f, 0.0f, 0.0f,
    0.0f,  0.5f, 0.5f,    0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
    0.0f, -0.5f, 0.0f,    xPos, yPos,   1.0f, 0.0f, 0.0f,
    0.0f, -0.5f, 0.0f,    xPos, yPos,   1.0f, 0.0f, 0.0f,
    0.0f,  0.5f, 0.5f,    0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
    0.0f,  0.5f, 0.0f,    xPos, 0.0f,   1.0f, 0.0f, 0.0f,

   -0.5f,  0.5f, 0.5f,    xPos,     yPos,   0.0f,  1.0f, 0.0f, 
   -0.5f,  0.5f, 0.0f,    xPos,     0.0f,   0.0f,  1.0f, 0.0f,
    0.0f,  0.5f, 0.5f,    xPos * 2, yPos,   0.0f,  1.0f, 0.0f,
    0.0f,  0.5f, 0.5f,    xPos * 2, yPos,   0.0f,  1.0f, 0.0f,
   -0.5f,  0.5f, 0.0f,    xPos,     0.0f,   0.0f,  1.0f, 0.0f,
    0.0f,  0.5f, 0.0f,    xPos * 2, 0.0f,   0.0f,  1.0f, 0.0f,

   -0.5f, -0.5f, 0.5f,    0.0f, yPos * 2,   0.0f, -1.0f, 0.0f,   
   -0.5f, -0.5f, 0.0f,    0.0f, yPos,       0.0f, -1.0f, 0.0f,
    0.0f, -0.5f, 0.5f,    xPos, yPos * 2,   0.0f, -1.0f, 0.0f,   
    0.0f, -0.5f, 0.5f,    xPos, yPos * 2,   0.0f, -1.0f, 0.0f,   
   -0.5f, -0.5f, 0.0f,    0.0f, yPos,       0.0f, -1.0f, 0.0f,
    0.0f, -0.5f, 0.0f,    xPos, yPos,       0.0f, -1.0f, 0.0f,
};

#endif // VERTICES_HPP
