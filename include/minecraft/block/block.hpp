#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "minecraft/block/blockenum.hpp"
#include "glm/vec3.hpp"


class Block
{
    public:
        Block(BlockName block, bool withSFX) noexcept;
        Block(BlockName block, bool withSFX, const glm::vec3 &blockPos) noexcept;
        glm::vec3 position {};
        float ambient {1.2f};
        inline BlockSoundID getSoundID() const noexcept {return id;}
        inline float getTextureID() const noexcept {return textureY;}
    private:
        BlockSoundID id;
        float textureY {};
        float initBlockTextureCoordinates(BlockName block) noexcept;
};

#endif // BLOCK_HPP
