#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "mylib/block.hpp"
#include "mylib/graphics/shader.hpp"
#include "mylib/window.hpp"
#include "mylib/camera.hpp"
#include "mylib/lighting.hpp"
#include <memory>

class Renderer
{
    public:
        Renderer(const Window* window);
        ~Renderer();
        void drawBlock(const Block& block, const glm::vec3& xyzPos);
        void drawChunk(const Block& block);
        void drawLightSource();
        void updateView(GLFWwindow* window);
        Shader cubeShader;
        std::unique_ptr<Camera> playerCamera;
    private:
		std::unique_ptr<Lighting> lightSource;
        unsigned int blockVao;
        unsigned int vertexBuffer;
};

#endif
