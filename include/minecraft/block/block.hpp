#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "minecraft/block/blockname.hpp"
#include "glm/vec3.hpp"


class Block
{
    public:
        Block(BlockName block, bool withSFX) noexcept;
        Block(BlockName block, const glm::vec3 &pos) noexcept;
        inline BlockName getName() const noexcept {return name;}
        inline float getTextureID() const noexcept {return textureY;}
        glm::vec3 position;
        float ambient {1.1f};
    private:
        BlockName name;
        float textureY;
        float initBlockTextureCoordinates(BlockName block) const noexcept;
};

#endif // BLOCK_HPP
