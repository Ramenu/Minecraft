#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "GLFW/glfw3.h"

namespace Window
{
    extern GLFWwindow *getWindow() noexcept;
    extern void initWindow(const char *windowName) noexcept;
    extern void processMovement(float deltaTime) noexcept; 
    static constexpr size_t width {512}, height {512};
    static constexpr float aspectRatio {width/height};
}

#endif // WINDOW_HPP