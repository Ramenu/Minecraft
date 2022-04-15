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

constexpr std::array<float, textureVerticesSize> getTextureVertices(float textureID)
{
    std::array<float, textureVerticesSize> textureVertices {
        0.0f,   yPos + textureID,
        xPos,   0.0f + textureID,
        xPos,   yPos + textureID,
        xPos,   0.0f + textureID,
        0.0f,   yPos + textureID,
        0.0f,   0.0f + textureID,

        0.0f,   yPos + textureID,
        xPos,   yPos + textureID,
        xPos,   0.0f + textureID,
        xPos,   0.0f + textureID,
        0.0f,   0.0f + textureID,
        0.0f,   yPos + textureID,

        xPos,   0.0f + textureID,
        0.0f,   yPos + textureID,
        xPos,   yPos + textureID,
        0.0f,   yPos + textureID,
        xPos,   0.0f + textureID,
        0.0f,   0.0f + textureID,

        xPos,   0.0f + textureID,
        xPos,   yPos + textureID,
        0.0f,   yPos + textureID,
        0.0f,   yPos + textureID,
        0.0f,   0.0f + textureID,
        xPos,   0.0f + textureID,

        xPos,   0.0f + textureID,
        xPos_2, yPos + textureID,
        xPos_2, 0.0f + textureID,
        xPos_2, yPos + textureID,
        xPos,   0.0f + textureID,
        xPos,   yPos + textureID,

        xPos_2, yPos + textureID,
        xPos_2, 0.0f + textureID,
        1.0f,   yPos + textureID,
        1.0f,   yPos + textureID,
        xPos_2, 0.0f + textureID,
        xPos_2, 0.0f + textureID
    };

    return textureVertices;

}

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

constexpr std::array<float, visibleVerticesSize> getVisibleBlockVertices(const std::array<float, noOfSquaresInCube> &visible)
{
    std::array<float, visibleVerticesSize> visibleVertices {
        1.0f * visible[0],
        1.0f * visible[0],
        1.0f * visible[0],
        1.0f * visible[0],
        1.0f * visible[0],
        1.0f * visible[0],

        1.0f * visible[1],
        1.0f * visible[1],
        1.0f * visible[1],
        1.0f * visible[1],
        1.0f * visible[1],
        1.0f * visible[1],

        1.0f * visible[2],
        1.0f * visible[2],
        1.0f * visible[2],
        1.0f * visible[2],
        1.0f * visible[2],
        1.0f * visible[2],

        1.0f * visible[3],
        1.0f * visible[3],
        1.0f * visible[3],
        1.0f * visible[3],
        1.0f * visible[3],
        1.0f * visible[3],

        1.0f * visible[4],
        1.0f * visible[4],
        1.0f * visible[4],
        1.0f * visible[4],
        1.0f * visible[4],
        1.0f * visible[4],

        1.0f * visible[5],
        1.0f * visible[5],
        1.0f * visible[5],
        1.0f * visible[5],
        1.0f * visible[5],
        1.0f * visible[5]
    };
    return visibleVertices;

}



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