#ifndef VERTICES_HPP
#define VERTICES_HPP

#include "minecraft/gfx/texture.hpp"
#include <vector>
#include <array>

using namespace Texture;

enum Attribute
{
    Position = 0,
    TexCoord = 1,
    LightDirection = 2,
    Visibility = 3
};

static constexpr size_t totalAttributes {4};

static constexpr size_t attributesToFormCube {36};

static constexpr size_t noOfSquaresInCube {6};


static constexpr size_t attributes[totalAttributes] {
    3, // Position 
    2, // Texture
    3, // Light direction
    1  // Visibility
};

static constexpr size_t posVerticesSize {attributes[Attribute::Position] * noOfSquaresInCube * noOfSquaresInCube},
                 textureVerticesSize {attributes[Attribute::TexCoord] * noOfSquaresInCube * noOfSquaresInCube},
                 lightDirVerticesSize {attributes[Attribute::LightDirection] * noOfSquaresInCube * noOfSquaresInCube},
                 visibleVerticesSize {attributes[Attribute::Visibility] * noOfSquaresInCube * noOfSquaresInCube},
                 noOfVertices {posVerticesSize + textureVerticesSize + lightDirVerticesSize + visibleVerticesSize};

static constexpr float xPos_2 {(atlasWidth - 1) * xPos};

struct ChunkVertex
{
    std::array<std::vector<float>, totalAttributes> attributes; 
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

static constexpr std::array<float, lightDirVerticesSize> defaultLightDirectionVertices {
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



[[maybe_unused]] static constexpr std::array<float, posVerticesSize> defaultPositionVertices {
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