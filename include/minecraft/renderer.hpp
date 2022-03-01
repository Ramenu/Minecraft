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
        ~Renderer();
        void bindBlock(BlockName block);
        void drawBlock(Block &block);
        void drawAllBlocks();
        void drawLightSource();
        void updateView();
        Shader cubeShader;
        Camera playerCamera;
        static void initProjection();
        static inline glm::mat4 getProjection() {return proj;}
    private:
        bool canHighlightBlock(const glm::vec3 &blockPos);
        Block selectedBlock;
		Lighting lightSource;
        uint32_t blockVao;
        BufferData vertexBuffer;
        static glm::mat4 proj;
        std::vector<Block> blocks;
};

#endif // RENDERER_HPP
