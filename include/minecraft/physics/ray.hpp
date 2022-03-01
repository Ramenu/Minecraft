#ifndef RAY_HPP
#define RAY_HPP

#include "minecraft/shader.hpp"
#include "minecraft/buffers/buffer.hpp"

class Ray
{
    public:
        Ray(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection, const glm::vec3 &rayLength);
        ~Ray();
        void updateRay();
        inline glm::vec3 getRay() const {return ray;}
        glm::vec3 origin;
        glm::vec3 direction;
        Shader rayShader;
        float rayPitch;
        float rayYaw;
        bool intersectsWith(const glm::vec3 &b);
    private:
        glm::vec3 ray;
        uint32_t vao;
        BufferData vertexBuffer;
        glm::vec3 length;
        uint32_t intersectionCount;
};

#endif // RAY_HPP
