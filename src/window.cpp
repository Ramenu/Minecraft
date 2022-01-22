#include "mylib/window.hpp"
#include "mylib/camera.hpp"
#include <stb-master/stb_image.h>
#include <iostream>

/* Handles keyboard-input.  */
void Window::processKeyboardInput(const double &deltaTime, Camera* camera)
{
    camera->movementSpeed = 2.5f * deltaTime;
    if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
        camera->cameraPos += camera->movementSpeed * camera->cameraFront;
    if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
        camera->cameraPos -= camera->movementSpeed * camera->cameraFront;
    if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
        camera->cameraPos -= camera->movementSpeed * camera->cameraRight;
    if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
        camera->cameraPos += camera->movementSpeed * camera->cameraRight;
    if (glfwGetKey(glfwWindow, GLFW_KEY_Q) == GLFW_PRESS)
        renderWireframes();
    if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(glfwWindow, true);
}

/* Handles main key events, like exiting the game, etc.*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (key)
    {
        case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, true); break;
    }
}

/* Enables/disables wireframes. */
void Window::renderWireframes()
{
    if (wireframeMode)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    wireframeMode = !wireframeMode;
}

/* Changes the screen viewport to its appropriate setting upon resize. Should be called once only, and when it is called, it should
   be when the window is being initialized. */
void framebuffer_size_callBack(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/* Class constructor for Window. Initializes a window of widthxheight. */
Window::Window(const unsigned int& width, const unsigned int& height) : screenWidth {width}, screenHeight {height}, wireframeMode {} {}

/* Class destructor for Window. */
Window::~Window()
{
    glfwDestroyWindow(glfwWindow);
}
//Method that loads the window and automatically does the tedious work, the window as 1st parameter and the name of it as the second
GLFWwindow* Window::loadWindow(GLFWwindow* window, const char* title)
{
    //Specify version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // If an apple machine (in this case, it isn't)
    #endif
    window = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL);

    //Occurs if window or OpenGL context creation fails (prints an error message and the title of the window)
    if (window == NULL)
    {
        glfwTerminate();
        printf("ERROR: Failed to contextualize window\n");
        exit(1);
    } 
    return window; 
}

/* Initializes the window. */
void Window::initWindow(const char* windowName)
{
    glfwWindow = loadWindow(glfwWindow, windowName);
    GLFWimage icon[1];
    icon[0].pixels = stbi_load("icons/icon.png", &icon[0].width, &icon[0].height, 0, 4);
    glfwSetWindowSize(glfwWindow, screenWidth, screenHeight);
    glfwSetWindowIcon(glfwWindow, 1, icon);
    glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callBack);
    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    stbi_image_free(icon[0].pixels);
}
/* Returns this window. */
GLFWwindow* Window::getWindow()
{
    return glfwWindow;
}

/* Makes this window the main context. */
void Window::makeContextCurrent()
{
    if (glfwWindow)
        glfwMakeContextCurrent(glfwWindow);
}
