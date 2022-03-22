#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "GLFW/glfw3.h"
#include "minecraft/camera/camera.hpp"

namespace Window
{
    inline GLFWwindow *window;
    extern GLFWwindow *loadWindow(GLFWwindow *window, const char &title) noexcept;
    extern void initWindow(const char *windowName) noexcept;
    extern void processKeyboardInput(double deltaTime, const CameraDirections &direction, glm::vec3 &pos) noexcept; 
    extern void renderWireframes() noexcept;
    extern void destroyWindow() noexcept;
    constexpr double width {512}, height {512};
}

#endif // WINDOW_HPP