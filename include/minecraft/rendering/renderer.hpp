#ifndef RENDERER_HPP
#define RENDERER_HPP

#define GLM_ENABLE_EXPERIMENTAL // For built-in glm hash

#include "minecraft/lighting/lighting.hpp"
#include "minecraft/camera/camera.hpp"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wduplicated-branches"
#include "glm/gtx/hash.hpp"
#pragma GCC diagnostic pop
#include <unordered_map>

static constexpr uint8_t noOfInactiveChunks {5};

static const glm::mat4 projection {[]() noexcept {
        static constexpr double fov {glm::radians(45.0)}, 
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
        void draw() const noexcept;
        void update() noexcept;
        Shader cubeShader;
    private:
		Lighting lightSource;
        void updateAdjacentChunks(const glm::u64vec3 &key) noexcept;
        void updateActiveChunks() noexcept;
        size_t activeChunkIndex {};
        std::unordered_map<glm::u64vec3, Chunk> allChunks;
        bool needsUpdate {true};
};

#endif // RENDERER_HPP
