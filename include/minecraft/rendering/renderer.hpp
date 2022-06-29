#ifndef MC_RENDERER_HPP
#define MC_RENDERER_HPP

#define GLM_ENABLE_EXPERIMENTAL // For built-in glm hash

#include "minecraft/camera/camera.hpp"
#include "minecraft/window/window.hpp"
#include "minecraft/shader/shader.hpp"
#if defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW64__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wduplicated-branches"
    #include "glm/gtx/hash.hpp"
    #pragma GCC diagnostic pop
#else
    #include "glm/gtx/hash.hpp"
#endif
#include <unordered_map>


class Renderer
{
    public:
        Renderer() noexcept;
        void draw() noexcept;
        void update() noexcept;
        inline Shader getShader() const noexcept { return cubeShader; }
    private:
        Shader cubeShader;
        void createChunkAndDraw(const glm::i32vec3 &chunkPos) noexcept;
        inline static bool chunkIsVisibleToPlayer(float x, float y, float z) noexcept {
            return (glm::dot(Camera::direction.front, {x, y, z}) > 0.0f);
        }
        void updateAdjacentChunks(const Chunk &chunk, const glm::i32vec3 &key) const noexcept;
        std::unordered_map<glm::i32vec3, Chunk> allChunks;
};

#endif // MC_RENDERER_HPP
