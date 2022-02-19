#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>
#include "mylib/camera.hpp"

namespace Window
{
    extern GLFWwindow* loadWindow(GLFWwindow* window, const char* title);
    extern void initWindow(const char* windowName, double windowWidth, double windowHeight);
    inline uint32_t screenWidth;
    inline uint32_t screenHeight;
    extern void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    extern void processKeyboardInput(float deltaTime, Camera* camera);
    extern void renderWireframes();
    extern void destroyWindow();
    inline bool wireframeMode;
    inline GLFWwindow* glfwWindow;
}

#endif // WINDOW_HPP