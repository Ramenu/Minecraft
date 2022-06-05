#ifndef MC_TEXTURE_HPP
#define MC_TEXTURE_HPP

#include "minecraft/block/blockenum.hpp"
#include <string>

static constexpr int atlasWidth {3}, atlasHeight {noBlocks - 1};
static constexpr float xPos {1.0f / atlasWidth}, yPos {1.0f / atlasHeight};

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
