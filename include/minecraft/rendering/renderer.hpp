#ifndef RENDERER_HPP
#define RENDERER_HPP

#define GLM_ENABLE_EXPERIMENTAL // For built-in glm hash

#include "minecraft/lighting/lighting.hpp"
#include "minecraft/camera/camera.hpp"
#if defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW64__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wduplicated-branches"
    #include "glm/gtx/hash.hpp"
    #pragma GCC diagnostic pop
#else
    #include "glm/gtx/hash.hpp"
#endif
#include <unordered_map>

static constexpr uint8_t noOfInactiveChunks {5};

static const glm::mat4 projection {glm::perspective(Camera::fov.value(), Window::aspectRatio, Camera::near, Camera::far)};


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
        inline static bool chunkIsVisibleToPlayer(float x, float y, float z) noexcept {
            return (glm::dot(Camera::direction.front, {x, y, z}) > 0.0f);
        }
        void updateAdjacentChunks(const glm::u64vec3 &key) noexcept;
        void updateActiveChunks() noexcept;
        size_t activeChunkIndex {};
        std::unordered_map<glm::u64vec3, Chunk> allChunks;
        bool needsUpdate {true};
};

#endif // RENDERER_HPP
