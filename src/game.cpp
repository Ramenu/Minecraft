#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include "mylib/game.hpp"
#include "mylib/renderer.hpp"
#include "mylib/lighting.hpp"
#include "mylib/glerror.hpp"
#include "mylib/window.hpp"
#include "mylib/gfx/texture.hpp"


/* Game constructor. Initializes the window width and height and GLFW itself. */
Game::Game(uint16_t windowWidth, uint16_t windowHeight) 
{
    glfwInit();
    Window::initWindow("Minecraft", windowWidth, windowHeight);
    glfwMakeContextCurrent(Window::getWindow());
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        GLError::error_message("Failed to initialize GLAD");

    glViewport(0, 0, windowWidth, windowHeight);
    Texture::initTextureAtlas();
    Lighting::initLightVAO();
    Renderer::initProjection();
}

/* Executes the game. */  
void Game::runGame()
{
    float deltaTime {0.0f}; // Time between current frame and last frame
    float lastFrame {0.0f}; // Time of last frame

    Renderer renderer;

    glEnable(GL_DEPTH_TEST);
    
    // Main game loop
    while (!glfwWindowShouldClose(Window::getWindow()))
    {
        const float currentTime {static_cast<float>(glfwGetTime())};
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        glClearColor(0.0f, 0.8f, 1.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.updateView();
        renderer.drawChunk();

        glfwSwapBuffers(Window::getWindow()); // Swap color buffer

        // Checks if any events are triggered (like keyboard input, etc)
        glfwPollEvents(); 
        Window::processKeyboardInput(deltaTime, renderer.playerCamera);
    }
    
}

Game::~Game()
{
    Texture::deleteTextureAtlas();
    Window::destroyWindow();
    glfwTerminate();
}

