#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "GLFW/glfw3.h"
#include "minecraft/camera.hpp"

namespace Window
{
    extern GLFWwindow *loadWindow(GLFWwindow *window, const char &title);
    extern void initWindow(const char *windowName);
    extern void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    extern void processKeyboardInput(double deltaTime, Camera &camera); 
    extern void renderWireframes();
    extern void destroyWindow();
    extern GLFWwindow *getWindow();
    constexpr double width {512}, height {512};
}

#endif // WINDOW_HPP