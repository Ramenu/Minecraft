#ifndef MC_RAY_HPP
#define MC_RAY_HPP

#include "glm/vec3.hpp"

inline unsigned int lineProgram;

class Ray
{
    public:
        Ray() : origin {0.0f, 0.0f, 0.0f} {}
        void initRay(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection, const glm::vec3 &rayLength) noexcept;
        ~Ray() noexcept;
        void updateRay(float xRotationRadians, float yRotationRadians, float zRotationRadians) noexcept;
        inline glm::vec3 getRay() const noexcept {return ray;}
        glm::vec3 origin;
        glm::vec3 direction;
        bool intersectsWith(const glm::vec3 &b) const noexcept;
        uint32_t vertexBuffer;
        uint32_t vao {};
        glm::vec3 ray {};
        glm::vec3 end {};
    private:
        glm::vec3 length;
};

#endif // MC_RAY_HPP