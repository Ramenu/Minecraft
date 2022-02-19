#include "glad/glad.h"
#include "mylib/window.hpp"
#include "mylib/camera.hpp"
#include "mylib/glerror.hpp"
#include <stb-master/stb_image.h>

namespace Window
{
    /* Handles keyboard-input.  */
    void processKeyboardInput(float deltaTime, Camera* camera)
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


    /* Enables/disables wireframes. */
    void renderWireframes()
    {
        if (wireframeMode)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        wireframeMode = !wireframeMode;
    }


    //Method that loads the window and automatically does the tedious work, the window as 1st parameter and the name of it as the second
    GLFWwindow* loadWindow(GLFWwindow* window, const char* title)
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
            GLError::error_message("Failed to contextualize window");
        } 
        return window; 
    }

    /* Destroys the window. */
    void destroyWindow()
    {
        if (glfwWindow)
            glfwDestroyWindow(glfwWindow);
    }

    /* Initializes the window. */
    void initWindow(const char* windowName, double windowWidth, double windowHeight)
    {
        screenWidth = windowWidth;
        screenHeight = windowHeight;
        glfwWindow = loadWindow(glfwWindow, windowName);
        GLFWimage icon[1];
        icon[0].pixels = stbi_load("icons/icon.png", &icon[0].width, &icon[0].height, 0, 4);
        glfwSetWindowSize(glfwWindow, screenWidth, screenHeight);
        glfwSetWindowIcon(glfwWindow, 1, icon);
        glfwSetFramebufferSizeCallback(glfwWindow, [](GLFWwindow*, int width, int height) {glViewport(0, 0, width, height);});
        glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        stbi_image_free(icon[0].pixels);
    }
}



