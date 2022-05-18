#ifndef RAY_HPP
#define RAY_HPP

#include "glm/vec3.hpp"

inline unsigned int lightProgram;

class Ray
{
    public:
        Ray() : origin {0.0f, 0.0f, 0.0f} {}
        void initRay(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection, const glm::vec3 &rayLength);
        ~Ray() noexcept;
        void updateRay();
        inline glm::vec3 getRay() const {return ray;}
        glm::vec3 origin;
        glm::vec3 direction;
        bool intersectsWith(const glm::vec3 &b) const noexcept;
        uint32_t vertexBuffer;
        uint32_t vao {};
    private:
        glm::vec3 ray {};
        glm::vec3 length;
};

#endif // RAY_HPP