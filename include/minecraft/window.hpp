#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "GLFW/glfw3.h"
#include "minecraft/camera.hpp"

namespace Window
{
    extern GLFWwindow *loadWindow(GLFWwindow *window, const char &title) noexcept;
    extern void initWindow(const char *windowName) noexcept;
    extern void processKeyboardInput(float deltaTime, Camera &camera) noexcept; 
    extern void renderWireframes() noexcept;
    extern void destroyWindow() noexcept;
    extern GLFWwindow *getWindow() noexcept;
    constexpr double width {512}, height {512};
}

#endif // WINDOW_HPP