#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include "minecraft/game.hpp"
#include "minecraft/renderer.hpp"
#include "minecraft/glerror.hpp"
#include "minecraft/window.hpp"
#include "minecraft/gfx/texture.hpp"


/**
 * Called upon the game's initialization.
 * Should be one of the first methods called
 * in the main function.
 */
Game::Game(const char *windowTitle) 
{
    glfwInit();
    Window::initWindow(windowTitle);
    glfwMakeContextCurrent(Window::getWindow());
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        GLError::error_message("Failed to initialize GLAD");

    constexpr float x {}, y {};
    glViewport(x, y, Window::width, Window::height);
    Texture::initTextureAtlas();
    Lighting::initLightVAO();
    Renderer::initProjection();
}

/**
 * Executes the game through an
 * infinite loop until the program
 * is terminated.
 */  
void Game::runGame()
{
    double deltaTime {0.0}; // Time between current frame and last frame
    double lastFrame {0.0}; // Time of last frame

    constexpr float red {0.0f}, green {0.8f}, blue {1.0f}, alpha {1.0f}; // RGB constants for the game's background colors (including alpha)
    Renderer renderer;

    glEnable(GL_DEPTH_TEST);
    
    // Main game loop
    while (!glfwWindowShouldClose(Window::getWindow()))
    {
        const double currentTime {glfwGetTime()};
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        glClearColor(red, green, blue, alpha);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.updateView();
        renderer.drawAllBlocks();

        glfwSwapBuffers(Window::getWindow()); // Swap color buffer

        // Checks if any events are triggered (like keyboard input, etc)
        glfwPollEvents(); 
        Window::processKeyboardInput(deltaTime, renderer.playerCamera);
    }
    
}

/**
 * Frees up remaining resources used by the game.
 */
Game::~Game() noexcept
{
    Texture::deleteTextureAtlas();
    Window::destroyWindow();
    glfwTerminate();
}

