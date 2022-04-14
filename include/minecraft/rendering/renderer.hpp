#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "minecraft/block/block.hpp"
#include "minecraft/camera/camera.hpp"
#include "minecraft/lighting/lighting.hpp"
#include "minecraft/rendering/chunk.hpp"
#include "minecraft/window/window.hpp"

constexpr uint8_t noOfInactiveChunks {5};

const glm::mat4 projection {[]{
        constexpr double fov {glm::radians(45.0)}, 
        aspectRatio {Window::width/Window::height}, 
        near {0.1}, 
        far {100.0};
        return glm::perspective(fov, aspectRatio, near, far);
    }()
};

class Renderer
{
    public:
        Renderer() noexcept;
        ~Renderer() noexcept;
        void drawLightSource() noexcept;
        void updateView() noexcept;
        void draw() const noexcept;
        Camera playerCamera;
    private:
        Shader cubeShader;
		Lighting lightSource;
        unsigned int vertexArray;
        unsigned int vertexBuffer;
        unsigned int lightVertexBuffer;
        //std::array<Chunk, noOfInactiveChunks> inactiveChunks;
};

#endif // RENDERER_HPP
