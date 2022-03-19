#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "minecraft/block/blockname.hpp"
#include "minecraft/block/material.hpp"


class Block
{
    public:
        Block(BlockName block, bool withSFX);
        Block(BlockName block, const glm::vec3 &blockPos);
        glm::vec3 position {};
        bool isDestroyed {false};
        void playDestroyedSound() const;
        Material blockMaterial;
        inline BlockName getName() const noexcept {return name;}
        inline float getTextureID() const noexcept {return textureY;}
    private:
        BlockName name;
        float textureY {};
        float initBlockTextureCoordinates(BlockName block) const noexcept;
};

#endif // BLOCK_HPP
