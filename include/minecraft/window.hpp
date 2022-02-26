#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "GLFW/glfw3.h"
#include "minecraft/camera.hpp"

namespace Window
{
    extern GLFWwindow* loadWindow(GLFWwindow* window, const char* title);
    extern void initWindow(const char* windowName, double windowWidth, double windowHeight);
    extern void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    extern void processKeyboardInput(float deltaTime, Camera& camera);
    extern void renderWireframes();
    extern void destroyWindow();
    extern GLFWwindow* getWindow();
    extern uint32_t getScreenWidth();
    extern uint32_t getScreenHeight();
}

#endif // WINDOW_HPP