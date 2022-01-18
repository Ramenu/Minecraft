#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
    public:
        Window(const unsigned int &width, const unsigned int &height);
        GLFWwindow* loadWindow(GLFWwindow* window, const char* title);
        void initWindow(const char* windowName);
        void makeContextCurrent();
        unsigned int screenWidth;
        unsigned int screenHeight;
        void processKeyMovement(const double &deltaTime);
        GLFWwindow* getWindow();
    private:
        void renderWireframes();
        bool wireframeMode;
        GLFWwindow* glfwWindow;
};

#endif