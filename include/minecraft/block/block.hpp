#ifndef MC_BLOCK_HPP
#define MC_BLOCK_HPP

#include "minecraft/block/blockenum.hpp"
#include "glm/vec3.hpp"
#include "minecraft/gfx/texture.hpp"
#include <array>


static constexpr std::array TEXTURE_COORDS {[](){
    std::array<float, NUMBER_OF_BLOCKS> coords {};
    for (uint8_t i {}; i < NUMBER_OF_BLOCKS; ++i)
        coords[i] = static_cast<float>(i) / ATLAS_HEIGHT;
    return coords;
}()};

class Block
{
    public:
        Block() = default;
        inline constexpr explicit Block(BlockName blockName) noexcept : name {blockName} {}
        inline float getTexture() const noexcept {
            return TEXTURE_COORDS[name - 1]; 
        }
        BlockName name;
};

#endif // MC_BLOCK_HPP
