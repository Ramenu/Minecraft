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
        std::unique_ptr<Shader> shader;
    private:
        unsigned int vao;
        unsigned int vertexBuffer;
};

#endif