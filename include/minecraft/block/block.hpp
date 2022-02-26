#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "minecraft/block/blockname.hpp"
#include "minecraft/block/material.hpp"


class Block
{
    public:
        Block() = default;
        Block(BlockName block, bool withSFX);
        glm::vec3 position;
        bool isDestroyed {false};
        Material blockMaterial;
        void playDestroyedSound() const;
        void draw() const;
        inline BlockName getBlockName() const {return name;}
        inline float getTextureID() const {return textureY;}
    private:
        BlockName name;
        float textureY;

};

#endif // BLOCK_HPP
