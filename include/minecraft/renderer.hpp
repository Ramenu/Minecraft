#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "minecraft/block/block.hpp"
#include "minecraft/camera.hpp"
#include "minecraft/lighting.hpp"
#include <vector>

class Renderer
{
    public:
        Renderer();
        ~Renderer() noexcept;
        void drawBlock(Block &block) noexcept;
        void drawAllBlocks() noexcept;
        void drawLightSource();
        void updateView();
        Camera playerCamera;
        static const glm::mat4 projection;
    private:
        Shader cubeShader;
        bool canHighlightBlock(const glm::vec3 &blockPos) const;
		Lighting lightSource;
        uint32_t blockVao {};
        BufferData vertexBuffer {};
        std::vector<Block> blocks {
            {BlockName::Grass_Block, {0.0f, 0.0f, 0.0f}},
            {BlockName::Grass_Block, {0.0f, 0.0f, 0.5f}},
            {BlockName::Grass_Block, {0.0f, 0.0f, 1.0f}},
            {BlockName::Grass_Block, {0.0f, 0.0f, 1.5f}},
            {BlockName::Grass_Block, {0.0f, 0.0f, 2.0f}},
            {BlockName::Grass_Block, {0.5f, 0.0f, 0.0f}},
            {BlockName::Grass_Block, {0.5f, 0.0f, 0.5f}},
            {BlockName::Grass_Block, {0.5f, 0.0f, 1.0f}},
            {BlockName::Grass_Block, {0.5f, 0.0f, 1.5f}},
            {BlockName::Grass_Block, {0.5f, 0.0f, 2.0f}},
            {BlockName::Grass_Block, {1.0f, 0.0f, 0.0f}},
            {BlockName::Grass_Block, {1.0f, 0.0f, 0.5f}},
            {BlockName::Grass_Block, {1.0f, 0.0f, 1.0f}},
            {BlockName::Grass_Block, {1.0f, 0.0f, 1.5f}},
            {BlockName::Grass_Block, {1.0f, 0.0f, 2.0f}},
            {BlockName::Grass_Block, {1.5f, 0.0f, 0.0f}},
            {BlockName::Grass_Block, {1.5f, 0.0f, 0.5f}},
            {BlockName::Grass_Block, {1.5f, 0.0f, 1.0f}},
            {BlockName::Grass_Block, {1.5f, 0.0f, 1.5f}},
            {BlockName::Grass_Block, {1.5f, 0.0f, 2.0f}},
            {BlockName::Grass_Block, {2.0f, 0.0f, 0.0f}},
            {BlockName::Grass_Block, {2.0f, 0.0f, 0.5f}},
            {BlockName::Grass_Block, {2.0f, 0.0f, 1.0f}},
            {BlockName::Grass_Block, {2.0f, 0.0f, 1.5f}},
            {BlockName::Grass_Block, {2.0f, 0.0f, 2.0f}},
        };
};

#endif // RENDERER_HPP
