#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "mylib/block/block.hpp"
#include "mylib/camera.hpp"
#include "mylib/lighting.hpp"

class Renderer
{
    public:
        Renderer();
        ~Renderer();
        void bindBlock(BlockName block);
        void drawBlock(const glm::vec3& xyzPos);
        void drawChunk();
        void drawLightSource();
        void updateView();
        Shader cubeShader;
        Camera playerCamera;
        static void initProjection();
        static inline glm::mat4 getProjection() {return proj;}
    private:
        bool canHighlightBlock(const glm::vec3& blockPos);
        Block selectedBlock;
		Lighting lightSource;
        uint32_t blockVao;
        BufferData vertexBuffer;
        static glm::mat4 proj;
};

#endif // RENDERER_HPP
