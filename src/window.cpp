#include "glad/glad.h"
#include "minecraft/window/window.hpp"
#include "minecraft/camera/camera.hpp"
#include "minecraft/glerror/glerror.hpp"
#include <stb-master/stb_image.h>

namespace Window
{
    static GLFWwindow *window;

    GLFWwindow *getWindow() noexcept {return window;}

    /**
     * Handles keyboard input.
     */
    void processMovement(float deltaTime, const CameraDirections &direction, glm::vec3 &pos) noexcept 
    {
        const float speedRate {speed * deltaTime};
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            pos += speedRate * direction.front;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            pos -= speedRate * direction.front;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            pos -= speedRate * direction.right;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            pos += speedRate * direction.right;
    }

    /**
     * Key callback for GLFW.
     */
    static void key_callback(GLFWwindow *glWindow, int key, int, int, int)
    {
        switch (key)
        {
            case GLFW_KEY_Q: return renderWireframes();
            case GLFW_KEY_ESCAPE: return glfwSetWindowShouldClose(glWindow, true);
        }
    }

    /**
     * Toggles wireframes. 
     */
    void renderWireframes() noexcept
    {
        // Make sure that Q is being pressed to prevent
        // constant switches
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            static constinit bool wireFrameMode = true;
            if ((wireFrameMode = !wireFrameMode))
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }


    //Method that loads the window and automatically does the tedious work, the window as 1st parameter and the name of it as the second
    GLFWwindow *loadWindow(GLFWwindow *glWindow, const char *title) noexcept
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

    /* Destroys the window. */
    void destroyWindow() noexcept
    {
        if (window != nullptr)
            glfwDestroyWindow(window);
    }

    /**
     * Initializes the window's width and height. Sets
     * the window's icon and the viewport.
     */
    void initWindow(const char *windowName) noexcept
    {
        window = loadWindow(window, windowName);
        GLFWimage icon[1];
        icon[0].pixels = stbi_load("./icons/icon.png", &icon[0].width, &icon[0].height, 0, 4);
        glfwSetWindowSize(window, width, height);
        glfwSetWindowIcon(window, 1, icon);
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int windowWidth, int windowHeight) {glViewport(0, 0, windowWidth, windowHeight);});
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetKeyCallback(window, key_callback);
        stbi_image_free(icon[0].pixels);
    }
}



