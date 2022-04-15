#ifndef VERTICES_HPP
#define VERTICES_HPP

#include "minecraft/rendering/chunk.hpp"
#include "glm/vec2.hpp"
#include "minecraft/gfx/texture.hpp"
#include <vector>

using namespace Texture;

constexpr size_t attributesToFormCube {36};

constexpr size_t noOfSquaresInCube {6};

constexpr size_t positionAttributeSize {3}, textureAttributeSize {2}, 
                 lightAttributeSize {3}, visibleAttributeSize {1}, 
                 allAttributeSize {positionAttributeSize + textureAttributeSize + lightAttributeSize + visibleAttributeSize};

constexpr size_t posVerticesSize {positionAttributeSize * noOfSquaresInCube * noOfSquaresInCube},
                 textureVerticesSize {textureAttributeSize * noOfSquaresInCube * noOfSquaresInCube},
                 lightDirVerticesSize {lightAttributeSize * noOfSquaresInCube * noOfSquaresInCube},
                 visibleVerticesSize {visibleAttributeSize * noOfSquaresInCube * noOfSquaresInCube},
                 noOfVertices {posVerticesSize + textureVerticesSize + lightDirVerticesSize + visibleVerticesSize};

constexpr float xPos_2 {(atlasWidth - 1) * xPos};

struct ChunkVertex
{
    std::vector<float> position;
    std::vector<float> texture;
    std::vector<float> lightDirection;
    std::vector<float> visibility;
};

constexpr std::array<float, posVerticesSize> createCubeAt(float x, float y, float z)
{
    const std::array<float, posVerticesSize> defaultPositionVertices {
        // Back (First square)
        -0.5f + x, -0.5f + y, 0.0f + z,
         0.0f + x,  0.5f + y, 0.0f + z,
         0.0f + x, -0.5f + y, 0.0f + z,
         0.0f + x,  0.5f + y, 0.0f + z,
        -0.5f + x, -0.5f + y, 0.0f + z,
        -0.5f + x,  0.5f + y, 0.0f + z,

        // Front (second square) 
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

        // Left square (fourth square)
        -0.5f + x,  0.5f + y, 0.0f + z,
        -0.5f + x, -0.5f + y, 0.0f + z,
        -0.5f + x, -0.5f + y, 0.5f + z,
        -0.5f + x, -0.5f + y, 0.5f + z,
        -0.5f + x,  0.5f + y, 0.5f + z,
        -0.5f + x,  0.5f + y, 0.0f + z,

        // Top square (fifth square)
        -0.5f + x,  0.5f + y, 0.0f + z,
         0.0f + x,  0.5f + y, 0.5f + z,
         0.0f + x,  0.5f + y, 0.0f + z,
         0.0f + x,  0.5f + y, 0.5f + z,
        -0.5f + x,  0.5f + y, 0.0f + z,
        -0.5f + x,  0.5f + y, 0.5f + z,

        // Bottom square (sixth square)
        -0.5f + x, -0.5f + y, 0.5f + z,
        -0.5f + x, -0.5f + y, 0.0f + z,
         0.0f + x, -0.5f + y, 0.5f + z,
         0.0f + x, -0.5f + y, 0.5f + z,
        -0.5f + x, -0.5f + y, 0.0f + z,
         0.0f + x, -0.5f + y, 0.0f + z
    };

    return defaultPositionVertices;
}


constexpr std::array<float, textureVerticesSize> defaultTextureVertices {
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

constexpr std::array<float, lightDirVerticesSize> defaultLightDirectionVertices {
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

constexpr std::array<float, visibleVerticesSize> defaultVisibleVertices {
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,

    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,

    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,

    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,

    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,

    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f
};

[[maybe_unused]] const std::array<float, posVerticesSize> defaultPositionVertices {
        // Back (First square)
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.0f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,

        // Fr(second,
        -0.5f, -0.5f, 0.5f,
         0.0f, -0.5f, 0.5f,
         0.0f,  0.5f, 0.5f,
         0.0f,  0.5f, 0.5f,
        -0.5f,  0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,

        // Ri(thir,
         0.0f,  0.5f, 0.0f,
         0.0f, -0.5f, 0.5f,
         0.0f, -0.5f, 0.0f,
         0.0f, -0.5f, 0.5f,
         0.0f,  0.5f, 0.0f,
         0.0f,  0.5f, 0.5f,

        // Lequare (th sq,
        -0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f,  0.5f, 0.5f,
        -0.5f,  0.5f, 0.0f,

        // Touare (f sq,
        -0.5f,  0.5f, 0.0f,
         0.0f,  0.5f, 0.5f,
         0.0f,  0.5f, 0.0f,
         0.0f,  0.5f, 0.5f,
        -0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.5f,

        // Bo squarexth sq,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.0f,
         0.0f, -0.5f, 0.5f,
         0.0f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.0f,
         0.0f, -0.5f, 0.0f
    };

#endif // VERTICES_HPP