#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "minecraft/block/blockenum.hpp"
#include <string>

constexpr uint8_t atlasWidth {3}, atlasHeight {noBlocks - 1};
constexpr float xPos {1.0f / atlasWidth}, yPos {1.0f / atlasHeight};

class Texture
{
    private:
        unsigned int texture;
    public:
        explicit Texture(const std::string &pathToTexture) noexcept;
        ~Texture() noexcept;
        inline unsigned int getTexture() const noexcept {return texture;}
};


#endif // TEXTURE_HPP
