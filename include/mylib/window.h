#ifndef WINDOW_H
#define WINDOW_H
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "mylib/camera.h"
#include <iostream>
#include <thread>
#include <chrono>

class Window{
    public:
        GLFWwindow* loadWindow(GLFWwindow* window, const char* title);
        void key_callback(GLFWwindow* window, float deltaTime);
        unsigned int screenWidth;
        unsigned int screenHeight;
        bool wireFrameMode;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void on_Mouse_Button(GLFWwindow* window, int button, int action, int mods);

#endif