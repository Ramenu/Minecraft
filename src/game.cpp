#define GLFW_INCLUDE_NONE
#define GAME_BENCHMARK

#include "minecraft/game/game.hpp"
#include "minecraft/rendering/renderer.hpp"
#include "minecraft/glerror/glerror.hpp"
#include "minecraft/window/window.hpp"
#include "minecraft/gfx/texture.hpp"
#ifdef GAME_BENCHMARK
    #include "timer.hpp"
#endif
#include "minecraft/data/uniformbuffer.h"


/**
 * Returns true if the debug output context
 * was successfully initialized.
 */
static bool initializedDebugContext()
{
    int flag;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flag);
    return (flag & GL_CONTEXT_FLAG_DEBUG_BIT);
}


/**
 * Called upon the game's initialization.
 * Should be one of the first methods called
 * in the main function.
 */
void initGame(const char *windowTitle) noexcept
{
    glfwInit();
    Window::initWindow(windowTitle);
    glfwMakeContextCurrent(Window::window);
    
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        GLError::error_message("Failed to initialize GLAD");
    
    // Check if initializing the debug context was successful (if on a debug build)
    #ifdef MC_DEBUG_BUILD
        if (!initializedDebugContext())
            GLError::error_message("Failed to initialize OpenGL debug context");
        GLError::enableGLDebugCallBack();
    #endif

    constexpr float x {}, y {};
    glViewport(x, y, Window::width, Window::height);
    Texture::initTextureAtlas();
    Lighting::initLightVAO();

    // Initialize uniform buffer, bind it, and store the data
    glGenBuffers(1, &uniformBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uniformBuffer, 0, sizeof(glm::mat4));
}

/**
 * Executes the game through an
 * infinite loop until the program
 * is terminated.
 */  
void runGame() noexcept
{
    double deltaTime {0.0}; // Time between current frame and last frame
    double lastFrame {0.0}; // Time of last frame

    Renderer renderer;
    #ifdef GAME_BENCHMARK
        Timer<std::milli> time;
    #endif
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    constexpr float red {0.0f}, green {0.8f}, blue {1.0f}, alpha {1.0f}; // RGB constants for the game's background colors (including alpha)
    glClearColor(red, green, blue, alpha);
    
    // Main game loop
    while (!glfwWindowShouldClose(Window::window))
    {
        #ifdef GAME_BENCHMARK
            time.start();
        #endif
        const double currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.updateView();
        renderer.drawChunk();

        glfwSwapBuffers(Window::window); // Swap color buffer
        
        // Checks if any events are triggered (like keyboard input, etc)
        glfwPollEvents(); 
        Window::processKeyboardInput(deltaTime, renderer.playerCamera.direction, renderer.playerCamera.cameraPos);
        #ifdef GAME_BENCHMARK
            time.end();
        #endif
    }

    // Free up remaining resources used by the game
    glDeleteBuffers(1, &uniformBuffer);
    Texture::deleteTextureAtlas();
    Window::destroyWindow();
    glfwTerminate();
    #ifdef GAME_BENCHMARK
        time.detailedDisplay();
    #endif
}
