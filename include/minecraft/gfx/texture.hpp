#ifndef MC_TEXTURE_HPP
#define MC_TEXTURE_HPP

#include "minecraft/block/blockenum.hpp"
#include <string>

static constexpr int ATLAS_WIDTH {3}, ATLAS_HEIGHT {NUMBER_OF_BLOCKS - 1};
static constexpr float X_POS {1.0f / ATLAS_WIDTH}, Y_POS {1.0f / ATLAS_HEIGHT};

class Texture
{
    private:
        unsigned int texture;
    public:
        explicit Texture(const std::string &pathToTexture) noexcept;
        ~Texture() noexcept;
        inline unsigned int getTexture() const noexcept {return texture;}
};


#endif // MC_TEXTURE_HPP
