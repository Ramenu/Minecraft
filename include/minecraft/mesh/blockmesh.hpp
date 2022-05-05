#ifndef BLOCKMESH_HPP
#define BLOCKMESH_HPP

#include "minecraft/gfx/texture.hpp"
#include <array>

static constexpr size_t attributesToFormCube {36};
static constexpr size_t noOfSquaresInCube {6};
static constexpr float xPos_2 {(atlasWidth - 1) * xPos};

enum Attribute
{
    Position,
    TexCoord,
    Visibility,
    Ambient
};

static constexpr std::array attributes {
    3, // Position 
    2, // Texture
    1, // Visibility
    1
};

static constexpr std::array<size_t, attributes.size()> verticesSizes {[](){
    std::array<size_t, attributes.size()> ver {};
    for (size_t i {}; i < ver.size(); i++)
        ver[i] = attributes[i] * noOfSquaresInCube * noOfSquaresInCube;
    return ver;
}()};

static constexpr size_t noOfVertices {[](){
    size_t sum {};
    for (const auto&i: verticesSizes)
        sum += i;
    return sum;
}()};

constexpr std::array<float, verticesSizes[Attribute::Ambient]> getAmbientVertices(float ambient) noexcept
{
    return {
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
        ambient,
    };
}

constexpr std::array<float, verticesSizes[Attribute::Position]> createCubeAt(float x, float y, float z) noexcept
{
    return {
        // Back (First square)
        -0.5f + x, -0.5f + y, -0.5f + z,
         0.5f + x,  0.5f + y, -0.5f + z,
         0.5f + x, -0.5f + y, -0.5f + z,
         0.5f + x,  0.5f + y, -0.5f + z,
        -0.5f + x, -0.5f + y, -0.5f + z,
        -0.5f + x,  0.5f + y, -0.5f + z,

        // Front (second square) 
        -0.5f + x, -0.5f + y, 0.5f + z,
         0.5f + x, -0.5f + y, 0.5f + z,
         0.5f + x,  0.5f + y, 0.5f + z,
         0.5f + x,  0.5f + y, 0.5f + z,
        -0.5f + x,  0.5f + y, 0.5f + z,
        -0.5f + x, -0.5f + y, 0.5f + z,

        // Right (third square)
         0.5f + x,  0.5f + y, -0.5f + z,
         0.5f + x, -0.5f + y,  0.5f + z,
         0.5f + x, -0.5f + y, -0.5f + z,
         0.5f + x, -0.5f + y,  0.5f + z,
         0.5f + x,  0.5f + y, -0.5f + z,
         0.5f + x,  0.5f + y,  0.5f + z,

        // Left square (fourth square)
        -0.5f + x,  0.5f + y, -0.5f + z,
        -0.5f + x, -0.5f + y, -0.5f + z,
        -0.5f + x, -0.5f + y,  0.5f + z,
        -0.5f + x, -0.5f + y,  0.5f + z,
        -0.5f + x,  0.5f + y,  0.5f + z,
        -0.5f + x,  0.5f + y, -0.5f + z,

        // Top square (fifth square)
        -0.5f + x,  0.5f + y, -0.5f + z,
         0.5f + x,  0.5f + y,  0.5f + z,
         0.5f + x,  0.5f + y, -0.5f + z,
         0.5f + x,  0.5f + y,  0.5f + z,
        -0.5f + x,  0.5f + y, -0.5f + z,
        -0.5f + x,  0.5f + y,  0.5f + z,

        // Bottom square (sixth square)
        -0.5f + x, -0.5f + y,  0.5f + z,
        -0.5f + x, -0.5f + y, -0.5f + z,
         0.5f + x, -0.5f + y,  0.5f + z,
         0.5f + x, -0.5f + y,  0.5f + z,
        -0.5f + x, -0.5f + y, -0.5f + z,
         0.5f + x, -0.5f + y, -0.5f + z
    };

}

constexpr std::array<float, verticesSizes[Attribute::TexCoord]> getTextureVertices(float textureID) noexcept
{
    std::array<float, verticesSizes[Attribute::TexCoord]> textureVertices {
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

constexpr std::array<float, verticesSizes[Attribute::Visibility]> 
getVisibleBlockVertices(const std::array<float, noOfSquaresInCube> &visible) noexcept
{
    std::array<float, verticesSizes[Attribute::Visibility]> visibleVertices {
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

#endif // BLOCKMESH_HPP
