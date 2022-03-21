#define GLFW_INCLUDE_NONE
#define GAME_BENCHMARK

#include "minecraft/game.hpp"
#include "minecraft/renderer.hpp"
#include "minecraft/glerror.hpp"
#include "minecraft/window.hpp"
#include "minecraft/gfx/texture.hpp"
#ifdef GAME_BENCHMARK
    #include "timer.hpp"
#endif


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

    constexpr float x {}, y {};
    glViewport(x, y, Window::width, Window::height);
    Texture::initTextureAtlas();
    Lighting::initLightVAO();
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

    constexpr float red {0.0f}, green {0.8f}, blue {1.0f}, alpha {1.0f}; // RGB constants for the game's background colors (including alpha)
    Renderer renderer;
    #ifdef GAME_BENCHMARK
        Timer<std::milli> time;
    #endif
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

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
        renderer.drawAllBlocks();

        glfwSwapBuffers(Window::window); // Swap color buffer
        
        // Checks if any events are triggered (like keyboard input, etc)
        glfwPollEvents(); 
        Window::processKeyboardInput(deltaTime, renderer.playerCamera.direction, renderer.playerCamera.cameraPos);
        #ifdef GAME_BENCHMARK
            time.end();
        #endif
    }

    // Free up remaining resources used by the game
    Texture::deleteTextureAtlas();
    Window::destroyWindow();
    glfwTerminate();
    #ifdef GAME_BENCHMARK
        time.detailedDisplay();
    #endif
}
