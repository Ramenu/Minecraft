#include "minecraft/data/vertices.hpp"
#include "minecraft/gfx/texture.hpp"
#include <iostream>

using namespace Texture;

constexpr float xPos_2 {(atlasWidth - 1) * xPos};


CubeVertex createCubeAt(float x, float y, float z) 
{
    CubeVertex cubeVertex;
    cubeVertex.lightDirectionVertices = {
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,

        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,

        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,

        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,

        0.0f,  1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,

        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f
    };

    cubeVertex.textureVertices = {
        0.0f,   yPos,
        xPos,   0.0f,
        xPos,   yPos,
        xPos,   0.0f,
        0.0f,   yPos,
        0.0f,   0.0f,

        0.0f,   yPos,
        xPos,   yPos,
        xPos,   0.0f,
        xPos,   0.0f,
        0.0f,   0.0f,
        0.0f,   yPos,

        xPos,   0.0f,
        0.0f,   yPos,
        xPos,   yPos,
        0.0f,   yPos,
        xPos,   0.0f,
        0.0f,   0.0f,

        xPos,   0.0f,
        xPos,   yPos,
        0.0f,   yPos,
        0.0f,   yPos,
        0.0f,   0.0f,
        xPos,   0.0f,

        xPos,   0.0f,
        xPos_2, yPos,
        xPos_2, 0.0f,
        xPos_2, yPos,
        xPos,   0.0f,
        xPos,   yPos,

        xPos_2, yPos,
        xPos_2, 0.0f,
        1.0f,   yPos,
        1.0f,   yPos,
        xPos_2, 0.0f,
        xPos_2, 0.0f
    };

    cubeVertex.positionVertices = {
        // Back (First square)
        -0.5f + x, -0.5f + y, 0.0f + z,
         0.0f + x,  0.5f + y, 0.0f + z,
         0.0f + x, -0.5f + y, 0.0f + z,
         0.0f + x,  0.5f + y, 0.0f + z,
        -0.5f + x, -0.5f + y, 0.0f + z,
        -0.5f + x,  0.5f + y, 0.0f + z,

        // Front (Second square)
        -0.5f + x, -0.5f + y, 0.5f + z,
         0.0f + x, -0.5f + y, 0.5f + z,
         0.0f + x,  0.5f + y, 0.5f + z,
         0.0f + x,  0.5f + y, 0.5f + z,
        -0.5f + x,  0.5f + y, 0.5f + z,
        -0.5f + x, -0.5f + y, 0.5f + z,

        // Right (third square)
         0.0f + x,  0.5f + y, 0.0f + z,
         0.0f + x, -0.5f + y, 0.5f + z,
         0.0f + x, -0.5f + y, 0.0f + z,
         0.0f + x, -0.5f + y, 0.5f + z,
         0.0f + x,  0.5f + y, 0.0f + z,
         0.0f + x,  0.5f + y, 0.5f + z,

        // Left (Fourth square)
        -0.5f + x,  0.5f + y, 0.0f + z,
        -0.5f + x, -0.5f + y, 0.0f + z,
        -0.5f + x, -0.5f + y, 0.5f + z,
        -0.5f + x, -0.5f + y, 0.5f + z,
        -0.5f + x,  0.5f + y, 0.5f + z,
        -0.5f + x,  0.5f + y, 0.0f + z,

        // Up (fifth square)
        -0.5f + x,  0.5f + y, 0.0f + z,
         0.0f + x,  0.5f + y, 0.5f + z,
         0.0f + x,  0.5f + y, 0.0f + z,
         0.0f + x,  0.5f + y, 0.5f + z,
        -0.5f + x,  0.5f + y, 0.0f + z,
        -0.5f + x,  0.5f + y, 0.5f + z,

        // Down (sixth square)
        -0.5f + x, -0.5f + y, 0.5f + z,
        -0.5f + x, -0.5f + y, 0.0f + z,
         0.0f + x, -0.5f + y, 0.5f + z,
         0.0f + x, -0.5f + y, 0.5f + z,
        -0.5f + x, -0.5f + y, 0.0f + z,
         0.0f + x, -0.5f + y, 0.0f + z
   };

   return cubeVertex;
}

std::vector<CubeVertex> initChunkVertices() 
{
    std::vector<CubeVertex> chunkVertices;

    // Note that the size of the vector is not the size of the chunkVolume
    // because x and z are incremented by 0.5f each time, so therefore it is 
    // actually chunkVolume * 2 * 2.
    for (float x {}; x < chunkWidth; x += 0.5f)
    {
        for (float y {}; y < chunkHeight; y += 1.0f)
        {
            for (float z {}; z < chunkLength; z += 0.5f)
            {
                chunkVertices.emplace_back(createCubeAt(x, y, z));
            }
        }
    }

    return chunkVertices;
}