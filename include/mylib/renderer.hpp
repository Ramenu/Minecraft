#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "mylib/block/block.hpp"
#include "mylib/shader.hpp"
#include "mylib/camera.hpp"
#include "mylib/lighting.hpp"
#include <memory>

class Renderer
{
    public:
        explicit Renderer();
        ~Renderer();
        void bindBlock(BlockName block);
        void drawBlock(glm::vec3&& xyzPos);
        void drawChunk();
        void drawLightSource();
        void updateView();
        Shader cubeShader;
        std::unique_ptr<Camera> playerCamera;
        static void initProjection();
        static inline glm::mat4 getProjection() {return proj;}
    private:
        Block selectedBlock;
		std::unique_ptr<Lighting> lightSource;
        uint32_t blockVao;
        uint32_t vertexBuffer;
        static glm::mat4 proj;
};

#endif // RENDERER_HPP
