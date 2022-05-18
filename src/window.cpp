#include "glad/glad.h"
#include "minecraft/window/window.hpp"
#include "minecraft/camera/camera.hpp"
#include "minecraft/glerror/glerror.hpp"
#include <stb-master/stb_image.h>

namespace Window
{
    static void renderWireFrames() noexcept;
    static GLFWwindow *loadWindow(GLFWwindow *glWindow, const char *title) noexcept;
    static GLFWwindow *window;

    GLFWwindow *getWindow() noexcept {return window;}

    /**
     * Handles keyboard input.
     */
    void processMovement(float deltaTime) noexcept 
    {
        using namespace Camera;
        const float speedRate {speed * deltaTime};
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += speedRate * direction.front;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= speedRate * direction.front;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= speedRate * direction.right;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += speedRate * direction.right;
    }

    /**
     * Key callback for GLFW.
     */
    static void key_callback(GLFWwindow *glWindow, int key, int, int, int) noexcept
    {
        switch (key)
        {
            case GLFW_KEY_Q: return renderWireFrames();
            case GLFW_KEY_ESCAPE: return glfwSetWindowShouldClose(glWindow, true);
        }
    }

    /**
     * Toggles wireframes. 
     */
    static void renderWireFrames() noexcept
    {
        // Make sure that Q is being pressed to prevent
        // constant switches
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            static constinit bool wireFrameMode {true};
            if ((wireFrameMode = !wireFrameMode)) // cppcheck-suppress knownConditionTrueFalse
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }

    void deleteWindow() noexcept
    {
        if (window)
            glfwDestroyWindow(window);
    }


    //Method that loads the window and automatically does the tedious work, the window as 1st parameter and the name of it as the second
    static GLFWwindow *loadWindow(GLFWwindow *glWindow, const char *title) noexcept
    {
        //Specify version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // If an apple machine (in this case, it isn't)
        #endif

        // Enable debug output context on debug builds
        #ifdef MC_DEBUG_BUILD
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true); 
        #endif

        glWindow = glfwCreateWindow(width, height, title, NULL, NULL);

        //Occurs if window or OpenGL context creation fails (prints an error message and the title of the window)
        if (!glWindow)
        {
            glfwTerminate();
            GLError::error_message("Failed to contextualize window");
        } 
        return glWindow; 
    }

    /**
     * Initializes the window's width and height. Sets
     * the window's icon and the viewport.
     */
    void initWindow(const char *windowName) noexcept
    {
        window = loadWindow(window, windowName);
        GLFWimage icon;
        icon.pixels = stbi_load("./icons/icon.png", &icon.width, &icon.height, 0, 0);
        glfwSetWindowSize(window, width, height);
        glfwSetWindowIcon(window, 1, &icon);
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int windowWidth, int windowHeight) {glViewport(0, 0, windowWidth, windowHeight);});
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetKeyCallback(window, key_callback);
        stbi_image_free(icon.pixels);
    }
}



