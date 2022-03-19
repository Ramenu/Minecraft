#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "minecraft/block/blockname.hpp"
#include "glm/vec3.hpp"


class Block
{
    public:
        Block(BlockName block, bool withSFX) noexcept;
        Block(BlockName block, bool withSFX, const glm::vec3 &blockPos) noexcept;
        glm::vec3 position {};
        float ambient {1.2f};
        inline BlockName getName() const noexcept {return name;}
        inline float getTextureID() const noexcept {return textureY;}
    private:
        BlockName name;
        float textureY {};
        float initBlockTextureCoordinates(BlockName block) const noexcept;
};

#endif // BLOCK_HPP
