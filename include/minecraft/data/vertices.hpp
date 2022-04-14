#ifndef VERTICES_HPP
#define VERTICES_HPP

#include "minecraft/rendering/chunk.hpp"
#include <vector>

constexpr size_t attributesToFormCube {36}, noOfSquaresInCube {6},
                 positionAttributeSize {3}, textureAttributeSize {2}, lightAttributeSize {3},
                 posVerticesSize {positionAttributeSize * noOfSquaresInCube * noOfSquaresInCube},
                 textureVerticesSize {textureAttributeSize * noOfSquaresInCube * noOfSquaresInCube},
                 lightDirVerticesSize {lightAttributeSize * noOfSquaresInCube * noOfSquaresInCube},
                 noOfVertices {posVerticesSize + textureVerticesSize + lightDirVerticesSize};

struct CubeVertex
{
    std::vector<float> positionVertices;
    std::vector<float> textureVertices;
    std::vector<float> lightDirectionVertices;
};


extern CubeVertex createCubeAt(float x, float y, float z);
extern std::vector<CubeVertex> initChunkVertices();


#endif // VERTICES_HPP
