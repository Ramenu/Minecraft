#ifndef MC_BLOCKMESH_HPP
#define MC_BLOCKMESH_HPP

#include "minecraft/gfx/texture.hpp"
#include <array>

static constexpr std::size_t CUBE_ATTRIBUTES {36};
static constexpr std::size_t SQUARES_ON_CUBE {6};
static constexpr float X_POS_2 {(ATLAS_WIDTH - 1) * X_POS};

enum Attribute : std::uint8_t
{
    Position,
    BlockID,
    Visibility,
    Ambient
};

static constexpr std::array ATTRIBUTES {
    3ull, // Position 
    1ull,
    1ull, // Visibility
    1ull  // Ambient
};

static constexpr std::array<std::size_t, ATTRIBUTES.size()> verticesSizes {[](){
    std::array<std::size_t, ATTRIBUTES.size()> ver {};
    for (std::size_t i {}; i < ver.size(); i++)
        ver[i] = ATTRIBUTES[i] * SQUARES_ON_CUBE * SQUARES_ON_CUBE;
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

constexpr std::array<float, verticesSizes[Attribute::BlockID]> getBlockIDVertices(BlockName block) noexcept
{
    const float blockf {static_cast<float>(block)};
    return {
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf,
        blockf
    };
}

#if 0
constexpr std::array<float, verticesSizes[Attribute::TexCoord]> getTextureVertices(float textureID) noexcept
{
    return {
        0.0f,    Y_POS + textureID,
        X_POS,   0.0f  + textureID,
        X_POS,   Y_POS + textureID,
        X_POS,   0.0f  + textureID,
        0.0f,    Y_POS + textureID,
        0.0f,    0.0f  + textureID,

        0.0f,    Y_POS + textureID,
        X_POS,   Y_POS + textureID,
        X_POS,   0.0f  + textureID,
        X_POS,   0.0f  + textureID,
        0.0f,    0.0f  + textureID,
        0.0f,    Y_POS + textureID,

        X_POS,   0.0f  + textureID,
        0.0f,    Y_POS + textureID,
        X_POS,   Y_POS + textureID,
        0.0f,    Y_POS + textureID,
        X_POS,   0.0f  + textureID,
        0.0f,    0.0f  + textureID,

        X_POS,   0.0f  + textureID,
        X_POS,   Y_POS + textureID,
        0.0f,    Y_POS + textureID,
        0.0f,    Y_POS + textureID,
        0.0f,    0.0f  + textureID,
        X_POS,   0.0f  + textureID,

        X_POS,   0.0f  + textureID,
        X_POS_2, Y_POS + textureID,
        X_POS_2, 0.0f  + textureID,
        X_POS_2, Y_POS + textureID,
        X_POS,   0.0f  + textureID,
        X_POS,   Y_POS + textureID,

        X_POS_2, Y_POS + textureID,
        X_POS_2, 0.0f  + textureID,
        1.0f,    Y_POS + textureID,
        1.0f,    Y_POS + textureID,
        X_POS_2, 0.0f  + textureID,
        X_POS_2, 0.0f  + textureID
    };

}
#endif

constexpr std::array<float, verticesSizes[Attribute::Visibility]> 
getVisibleBlockVertices(const std::array<float, SQUARES_ON_CUBE> &visible) noexcept
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
