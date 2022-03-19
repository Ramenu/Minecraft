#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "minecraft/block/block.hpp"
#include "minecraft/camera.hpp"
#include "minecraft/lighting.hpp"
#include <vector>

class Renderer
{
    public:
        Renderer() noexcept;
        ~Renderer() noexcept;
        bool drawBlock(Block &block) noexcept;
        void drawAllBlocks() noexcept;
        void drawLightSource() noexcept;
        void updateView() noexcept;
        Camera playerCamera;
        static const glm::mat4 projection;
    private:
        Shader cubeShader;
        bool canHighlightBlock(const glm::vec3 &blockPos) const noexcept;
		Lighting lightSource;
        uint32_t blockVao {};
        BufferData vertexBuffer {};
        std::vector<Block> blocks {
            {BlockName::Grass_Block, false, {0.0f, 0.0f, 0.0f}},
            {BlockName::Grass_Block, false, {0.0f, 0.0f, 0.5f}},
            {BlockName::Grass_Block, false, {0.0f, 0.0f, 1.0f}},
            {BlockName::Grass_Block, false, {0.0f, 0.0f, 1.5f}},
            {BlockName::Grass_Block, false, {0.0f, 0.0f, 2.0f}},
            {BlockName::Grass_Block, false, {0.5f, 0.0f, 0.0f}},
            {BlockName::Grass_Block, false, {0.5f, 0.0f, 0.5f}},
            {BlockName::Grass_Block, false, {0.5f, 0.0f, 1.0f}},
            {BlockName::Grass_Block, false, {0.5f, 0.0f, 1.5f}},
            {BlockName::Grass_Block, false, {0.5f, 0.0f, 2.0f}},
            {BlockName::Grass_Block, false, {1.0f, 0.0f, 0.0f}},
            {BlockName::Grass_Block, false, {1.0f, 0.0f, 0.5f}},
            {BlockName::Grass_Block, false, {1.0f, 0.0f, 1.0f}},
            {BlockName::Grass_Block, false, {1.0f, 0.0f, 1.5f}},
            {BlockName::Grass_Block, false, {1.0f, 0.0f, 2.0f}},
            {BlockName::Grass_Block, false, {1.5f, 0.0f, 0.0f}},
            {BlockName::Grass_Block, false, {1.5f, 0.0f, 0.5f}},
            {BlockName::Grass_Block, false, {1.5f, 0.0f, 1.0f}},
            {BlockName::Grass_Block, false, {1.5f, 0.0f, 1.5f}},
            {BlockName::Grass_Block, false, {1.5f, 0.0f, 2.0f}},
            {BlockName::Grass_Block, false, {2.0f, 0.0f, 0.0f}},
            {BlockName::Grass_Block, false, {2.0f, 0.0f, 0.5f}},
            {BlockName::Grass_Block, false, {2.0f, 0.0f, 1.0f}},
            {BlockName::Grass_Block, false, {2.0f, 0.0f, 1.5f}},
            {BlockName::Grass_Block, false, {2.0f, 0.0f, 2.0f}},
        };
};

#endif // RENDERER_HPP
