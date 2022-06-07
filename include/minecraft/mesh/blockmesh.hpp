#ifndef MC_BLOCKMESH_HPP
#define MC_BLOCKMESH_HPP

#include "minecraft/gfx/texture.hpp"
#include <array>

static constexpr std::size_t attributesToFormCube {36};
static constexpr std::size_t noOfSquaresInCube {6};
static constexpr float xPos_2 {(atlasWidth - 1) * xPos};

enum Attribute : std::uint8_t
{
    Position,
    TexCoord,
    Visibility,
    Ambient
};

static constexpr std::array attributes {
    3ull, // Position 
    2ull, // Texture
    1ull, // Visibility
    1ull
};

static constexpr std::array<std::size_t, attributes.size()> verticesSizes {[](){
    std::array<std::size_t, attributes.size()> ver {};
    for (std::size_t i {}; i < ver.size(); i++)
        ver[i] = attributes[i] * noOfSquaresInCube * noOfSquaresInCube;
    return ver;
}()};

static constexpr std::size_t noOfVertices {[](){
    std::size_t sum {};
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
    return {
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

}

constexpr std::array<float, verticesSizes[Attribute::Visibility]> 
getVisibleBlockVertices(const std::array<float, noOfSquaresInCube> &visible) noexcept
{
    return {
        visible[0],
        visible[0],
        visible[0],
        visible[0],
        visible[0],
        visible[0],

        visible[1],
        visible[1],
        visible[1],
        visible[1],
        visible[1],
        visible[1],

        visible[2],
        visible[2],
        visible[2],
        visible[2],
        visible[2],
        visible[2],

        visible[3],
        visible[3],
        visible[3],
        visible[3],
        visible[3],
        visible[3],

        visible[4],
        visible[4],
        visible[4],
        visible[4],
        visible[4],
        visible[4],

        visible[5],
        visible[5],
        visible[5],
        visible[5],
        visible[5],
        visible[5]
    };

}

#endif // MC_BLOCKMESH_HPP
