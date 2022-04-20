#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "glm/vec3.hpp"
#include "minecraft/window/window.hpp"
#include <string>

inline void setTitle(const glm::vec3 &vec) noexcept
{
    std::string_view s {std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z)};
    glfwSetWindowTitle(Window::getWindow(), s.data());
}

#endif // DEBUG_HPP
