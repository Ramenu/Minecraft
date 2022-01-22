#include "mylib/vertices.hpp"
#include "mylib/graphics/textures.hpp"

const float cubeVertices[180]
{
   -0.5f, -0.5f, 0.0f,    0.0f, yPos,   
   -0.5f,  0.5f, 0.0f,    0.0f, 0.0f,   
    0.0f, -0.5f, 0.0f,    xPos, yPos,   
    0.0f, -0.5f, 0.0f,    xPos, yPos,   
   -0.5f,  0.5f, 0.0f,    0.0f, 0.0f,   
    0.0f,  0.5f, 0.0f,    xPos, 0.0f,   

   -0.5f, -0.5f, 0.5f,    0.0f, yPos,   
   -0.5f,  0.5f, 0.5f,    0.0f, 0.0f,   
    0.0f, -0.5f, 0.5f,    xPos, yPos,   
    0.0f, -0.5f, 0.5f,    xPos, yPos,   
   -0.5f,  0.5f, 0.5f,    0.0f, 0.0f,   
    0.0f,  0.5f, 0.5f,    xPos, 0.0f,   

   -0.5f, -0.5f, 0.5f,	  0.0f, yPos,  
   -0.5f,  0.5f, 0.5f,	  0.0f, 0.0f,  
   -0.5f, -0.5f, 0.0f,    xPos, yPos,   
   -0.5f, -0.5f, 0.0f,	  xPos, yPos, 
   -0.5f,  0.5f, 0.5f,	  0.0f, 0.0f, 
   -0.5f,  0.5f, 0.0f,	  xPos, 0.0f, 

    0.0f, -0.5f, 0.5f,    0.0f, yPos,   
    0.0f,  0.5f, 0.5f,    0.0f, 0.0f,   
    0.0f, -0.5f, 0.0f,    xPos, yPos,   
    0.0f, -0.5f, 0.0f,    xPos, yPos,   
    0.0f,  0.5f, 0.5f,    0.0f, 0.0f,   
    0.0f,  0.5f, 0.0f,    xPos, 0.0f,   

   -0.5f,  0.5f, 0.5f,    xPos,     yPos,   
   -0.5f,  0.5f, 0.0f,    xPos,     0.0f,   
    0.0f,  0.5f, 0.5f,    xPos * 2, yPos,   
    0.0f,  0.5f, 0.5f,    xPos * 2, yPos,   
   -0.5f,  0.5f, 0.0f,    xPos,     0.0f,   
    0.0f,  0.5f, 0.0f,    xPos * 2, 0.0f,   

   -0.5f, -0.5f, 0.5f,    0.0f, yPos * 2,   
   -0.5f, -0.5f, 0.0f,    0.0f, yPos,   
    0.0f, -0.5f, 0.5f,    xPos, yPos * 2,   
    0.0f, -0.5f, 0.5f,    xPos, yPos * 2,   
   -0.5f, -0.5f, 0.0f,    0.0f, yPos,   
    0.0f, -0.5f, 0.0f,    xPos, yPos,   
};

/*const float cubeVertices[180]
{
   -0.5f, -0.5f, 0.0f,    1.0f * xPos, 1.0f * yPos + yPos,  
   -0.5f,  0.5f, 0.0f,    1.0f * xPos, 1.0f * yPos, 
    0.0f, -0.5f, 0.0f,    1.0f * xPos + xPos, 1.0f * yPos + yPos,
    0.0f, -0.5f, 0.0f,    1.0f * xPos + xPos, 1.0f * yPos + yPos,
   -0.5f,  0.5f, 0.0f,    1.0f * xPos, 1.0f * yPos,
    0.0f,  0.5f, 0.0f,    1.0f * xPos + xPos, 1.0f * yPos,

   -0.5f, -0.5f, 0.5f,    0.5f, 0.5f,
   -0.5f,  0.5f, 0.5f,    0.0f, 0.0f,
    0.0f, -0.5f, 0.5f,    xPos, yPos,
    0.0f, -0.5f, 0.5f,    xPos, yPos,
   -0.5f,  0.5f, 0.5f,    0.0f, 0.0f,
    0.0f,  0.5f, 0.5f,    xPos, 0.0f,

   -0.5f, -0.5f, 0.5f,	  0.0f, yPos,
   -0.5f,  0.5f, 0.5f,	  0.0f, 0.0f,
   -0.5f, -0.5f, 0.0f,    xPos, yPos,
   -0.5f, -0.5f, 0.0f,	  xPos, yPos,
   -0.5f,  0.5f, 0.5f,	  0.0f, 0.0f,
   -0.5f,  0.5f, 0.0f,	  xPos, 0.0f,

    0.0f, -0.5f, 0.5f,    0.0f, yPos,
    0.0f,  0.5f, 0.5f,    0.0f, 0.0f,
    0.0f, -0.5f, 0.0f,    xPos, yPos,
    0.0f, -0.5f, 0.0f,    xPos, yPos,
    0.0f,  0.5f, 0.5f,    0.0f, 0.0f,
    0.0f,  0.5f, 0.0f,    xPos, 0.0f,
        
   -0.5f,  0.5f, 0.5f,    0.0f, yPos,
   -0.5f,  0.5f, 0.0f,    0.0f, 0.0f,
    0.0f,  0.5f, 0.5f,    xPos + xPos, yPos,
    0.0f,  0.5f, 0.5f,    xPos + xPos, yPos,
   -0.5f,  0.5f, 0.0f,    0.0f, 0.0f,
    0.0f,  0.5f, 0.0f,    xPos + xPos, 0.0f,

   -0.5f, -0.5f, 0.5f,    0.0f, yPos + yPos,
   -0.5f, -0.5f, 0.0f,    0.0f, 0.0f,
    0.0f, -0.5f, 0.5f,    xPos, yPos + yPos,
    0.0f, -0.5f, 0.5f,    xPos, yPos + yPos,
   -0.5f, -0.5f, 0.0f,    0.0f, 0.0f,
    0.0f, -0.5f, 0.0f,    xPos, 0.0f
};


const float cubeVertices[24]
{
    // First square
    -0.5f, -0.5f, 0.0f,    
    -0.5f,  0.5f, 0.0f,     
     0.5f, -0.5f, 0.0f,     
     0.5f,  0.5f, 0.0f,      

    // Second square
    -0.5f, -0.5f, 1.0f,   
    -0.5f,  0.5f, 1.0f,    
     0.5f, -0.5f, 1.0f,   
     0.5f,  0.5f, 1.0f,   
};

const unsigned int indices[36]
{
    0, 1, 2, 
    1, 2, 3,
    4, 5, 6,
    5, 6, 7,
    0, 1, 4,
    4, 5, 1,
    2, 3, 6,
    3, 7, 6,
    0, 2, 4,
    2, 6, 4,
    1, 3, 5,
    3, 7, 5
};*/
