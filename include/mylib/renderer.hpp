#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "mylib/block.hpp"
#include "mylib/graphics/shader.hpp"
#include "mylib/window.hpp"
#include <memory>

class Renderer
{
    public:
        Renderer(const Window* window);
        ~Renderer();
        void drawChunk(const Block& block);
        void drawLightSource();
        void updateView(glm::mat4& viewMatrix);
        Shader cubeShader;
        Shader lightShader;
    private:
        unsigned int blockVao;
        unsigned int lightVao;
        unsigned int vertexBuffer;
};

#endif