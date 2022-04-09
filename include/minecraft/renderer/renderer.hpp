#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "minecraft/block/block.hpp"
#include "minecraft/camera/camera.hpp"
#include "minecraft/lighting/lighting.hpp"
#include "minecraft/buffer/buffer.hpp"
#include <vector>

class Renderer
{
    public:
        Renderer() noexcept;
        ~Renderer() noexcept;
        void drawBlock(size_t blockIndice) noexcept;
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
        unsigned int vertexBuffer;
        static std::vector<Block> initBlockPositions();
        std::vector<Block> blocks {initBlockPositions()};
};

#endif // RENDERER_HPP
