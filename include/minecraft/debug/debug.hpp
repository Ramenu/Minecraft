#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "glm/vec3.hpp"
#include "GLFW/glfw3.h"
#include "minecraft/window/window.hpp"
#include <string>

inline void setTitle(const glm::vec3 &vec, bool normalize)
{
    glm::vec3 b {vec};
    if (normalize)
        b = glm::normalize(vec);
    std::string_view s {std::to_string(b.x) + ", " + std::to_string(b.y) + ", " + std::to_string(b.z)};
    glfwSetWindowTitle(Window::window, s.data());
}

#endif // DEBUG_HPP
