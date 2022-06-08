#ifndef MC_DEBUG_HPP
#define MC_DEBUG_HPP

#include "glm/vec3.hpp"
#include "minecraft/window/window.hpp"
#include <string>
#include <cmath>

inline void setTitle(const glm::vec3 &vec) noexcept
{
    std::string s {std::to_string(std::round(vec.x)) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z)};
    glfwSetWindowTitle(Window::getWindow(), s.c_str());
}

#endif // MC_DEBUG_HPP
