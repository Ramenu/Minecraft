#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "GLFW/glfw3.h"
#include <cstdint>

namespace Window
{
    extern GLFWwindow *getWindow() noexcept;
    extern void initWindow(const char *windowName) noexcept;
    extern void processMovement(float deltaTime) noexcept; 
    extern void deleteWindow() noexcept;
    static constexpr std::size_t WIDTH {512}, HEIGHT {512};
    static constexpr float ASPECT_RATIO {WIDTH/HEIGHT};
    inline bool runningInDebugMode {false};
}

#endif // WINDOW_HPP