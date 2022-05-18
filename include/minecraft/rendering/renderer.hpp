#ifndef RENDERER_HPP
#define RENDERER_HPP

#define GLM_ENABLE_EXPERIMENTAL // For built-in glm hash

#include "minecraft/lighting/lighting.hpp"
#include "minecraft/camera/camera.hpp"
#include "minecraft/window/window.hpp"
#if defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW64__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wduplicated-branches"
    #include "glm/gtx/hash.hpp"
    #pragma GCC diagnostic pop
#else
    #include "glm/gtx/hash.hpp"
#endif
#include <unordered_map>

static constexpr std::uint8_t noOfInactiveChunks {5};

static const glm::mat4 projection {glm::perspective(Camera::fov.value(), Window::aspectRatio, Camera::near, Camera::far)};


class Renderer
{
    public:
        Renderer() noexcept;
        void draw() const noexcept;
        void update() noexcept;
        Shader cubeShader;
    private:
		Lighting lightSource;
        inline static bool chunkIsVisibleToPlayer(float x, float y, float z) noexcept {
            return (glm::dot(Camera::direction.front, {x, y, z}) > 0.0f);
        }
        void updateAdjacentChunks(const std::array<std::array<std::array<Block, chunkLength>, chunkHeight>, chunkWidth> &chunk,
                                  const glm::u64vec3 &key) const noexcept;
        void updateActiveChunks() const noexcept;
        std::unordered_map<glm::u64vec3, Chunk> allChunks;
        bool needsUpdate {true};
};

#endif // RENDERER_HPP
