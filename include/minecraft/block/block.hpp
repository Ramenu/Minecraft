#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "minecraft/block/blockname.hpp"
#include "minecraft/block/material.hpp"


class Block
{
    public:
        Block() = default;
        Block(BlockName block, bool withSFX);
        Block(BlockName block, const glm::vec3 &blockPos);
    private:
        BlockName name;
        void initBlockTextureCoordinates(BlockName block);
        float textureY {};
    public:
        glm::vec3 position {};
        bool isDestroyed {false};
        void playDestroyedSound() const;
        BlockName getBlockName() const {return name;}
        inline float getTextureID() const {return textureY;}
        Material blockMaterial;
};

#endif // BLOCK_HPP
