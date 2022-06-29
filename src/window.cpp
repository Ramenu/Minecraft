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
        const float speedRate {Camera::SPEED * deltaTime};
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            Camera::cameraPos += speedRate * Camera::direction.front;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            Camera::cameraPos -= speedRate * Camera::direction.front;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            Camera::cameraPos -= speedRate * Camera::direction.right;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            Camera::cameraPos += speedRate * Camera::direction.right;
    }

    /**
     * Key callback for GLFW.
     */
    static void key_callback(GLFWwindow *glWindow, int key, int /*unused*/, int /*unused*/, int /*unused*/) noexcept
    {
        static constexpr int CLOSE_WINDOW {1};
        switch (key)
        {
            case GLFW_KEY_Q: return renderWireFrames();
            case GLFW_KEY_ESCAPE: return glfwSetWindowShouldClose(glWindow, CLOSE_WINDOW);
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
            if ((wireFrameMode = !wireFrameMode))// cppcheck-suppress knownConditionTrueFalse
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }

    void deleteWindow() noexcept
    {
        if (window != nullptr)
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
        #ifndef NDEBUG
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true); 
        #endif

        glWindow = glfwCreateWindow(WIDTH, HEIGHT, title, nullptr, nullptr);

        //Occurs if window or OpenGL context creation fails (prints an error message and the title of the window)
        if (glWindow == nullptr)
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
        icon.pixels = stbi_load("./icons/icon.png", &icon.width, &icon.height, nullptr, 0);
        glfwSetWindowSize(window, WIDTH, HEIGHT);
        glfwSetWindowIcon(window, 1, &icon);
        static constexpr int viewportX {0};
        static constexpr int viewportY {0};
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int windowWIDTH, int windowHeight) {glViewport(viewportX, viewportY, windowWIDTH, windowHeight);});
        const int cursorMode {runningInDebugMode ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED};
        glfwSetInputMode(window, GLFW_CURSOR, cursorMode);
        glfwSetKeyCallback(window, key_callback);
        stbi_image_free(icon.pixels);
    }
}



