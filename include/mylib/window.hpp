#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "mylib/camera.hpp"

class Window
{
    public:
        Window(const unsigned int &width, const unsigned int &height);
        ~Window();
        GLFWwindow* loadWindow(GLFWwindow* window, const char* title);
        void initWindow(const char* windowName);
        void makeContextCurrent();
        unsigned int screenWidth;
        unsigned int screenHeight;
        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        void processKeyboardInput(const double& deltaTime, Camera* camera);
        GLFWwindow* getWindow();
    private:
        void renderWireframes();
        bool wireframeMode;
        GLFWwindow* glfwWindow;
};

#endif