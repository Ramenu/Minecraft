#include "mylib/window.hpp"
#include "mylib/camera.hpp"
#include <stb-master/stb_image.h>
#include <iostream>

void Window::processKeyMovement(const double &deltaTime)
{
    playerCamera->movementSpeed = 2.5f * deltaTime;
    if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
        playerCamera->cameraPos += playerCamera->movementSpeed * playerCamera->cameraFront;
    if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
        playerCamera->cameraPos -= playerCamera->movementSpeed * playerCamera->cameraFront;
    if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
        playerCamera->cameraPos -= playerCamera->movementSpeed * playerCamera->cameraRight;
    if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
        playerCamera->cameraPos += playerCamera->movementSpeed * playerCamera->cameraRight;
    if (glfwGetKey(glfwWindow, GLFW_KEY_Q) == GLFW_PRESS)
        renderWireframes();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (key)
    {
        case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, true); break;
    }
}


void Window::renderWireframes()
{
    if (wireframeMode)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    wireframeMode = !wireframeMode;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (playerCamera->firstMouseMovement)
    {
        playerCamera->lastX = xpos;
        playerCamera->lastY = ypos;
        playerCamera->firstMouseMovement = false;
    }

    double xOffset {xpos - playerCamera->lastX};
    double yOffset {playerCamera->lastY - ypos}; // y-axis is reversed, which is why the order is flipped

    // Update the last mouse positions to the current position
    playerCamera->lastX = xpos;
    playerCamera->lastY = ypos;

    xOffset *= playerCamera->mouseSensitivity;
    yOffset *= playerCamera->mouseSensitivity;

    playerCamera->yaw += xOffset;
    playerCamera->pitch += yOffset;

    // To prevent the player from turning past a certain angle
    if (playerCamera->pitch > 89.0f)
        playerCamera->pitch = 89.0f;
    else if (playerCamera->pitch < -89.0f)
        playerCamera->pitch = -89.0f;
}

/* Changes the screen viewport to its appropriate setting upon resize. Should be called once only, and when it is called, it should
   be when the window is being initialized. */
void framebuffer_size_callBack(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/* Class constructor for Window. Initializes a window of widthxheight. */
Window::Window(const unsigned int& width, const unsigned int& height) : screenWidth {width}, screenHeight {height}, wireframeMode {} {}

//Method that loads the window and automatically does the tedious work, the window as 1st parameter and the name of it as the second
GLFWwindow* Window::loadWindow(GLFWwindow* window, const char* title)
{
    //Specify version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //If an apple machine (in this case, it isn't)
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
    glfwSetWindowIcon(glfwWindow, 1, icon);
    glfwSetKeyCallback(glfwWindow, key_callback);
    glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callBack);
    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPosCallback(glfwWindow, mouse_callback);
    stbi_image_free(icon[0].pixels);
}
/* Returns this window. */
GLFWwindow* Window::getWindow()
{
    return glfwWindow;
}


/* Handles keyboard input from the user. */

void Window::makeContextCurrent()
{
    if (glfwWindow)
        glfwMakeContextCurrent(glfwWindow);
}
