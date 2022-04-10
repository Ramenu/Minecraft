#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "minecraft/block/block.hpp"
#include "minecraft/camera/camera.hpp"
#include "minecraft/lighting/lighting.hpp"
#include "minecraft/buffer/buffer.hpp"
#include "minecraft/rendering/chunk.hpp"

class Renderer
{
    public:
        Renderer() noexcept;
        ~Renderer() noexcept;
        void drawBlock(Block &block, const glm::vec3 &blockIndex) noexcept;
        void drawLightSource() noexcept;
        void updateView() noexcept;
        void drawChunk() noexcept;
        Camera playerCamera;
        static const glm::mat4 projection;
    private:
        Shader cubeShader;
        bool canHighlightBlock(const glm::vec3 &blockPos) const noexcept;
		Lighting lightSource;
        uint32_t blockVao {};
        unsigned int vertexBuffer;
        Chunk terrain {BlockName::Grass_Block, BlockName::Dirt_Block};
};

#endif // RENDERER_HPP
