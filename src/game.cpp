#define GLFW_INCLUDE_NONE
#define LENGTHOF(a) sizeof(a)/sizeof(*a)

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include "mylib/game.hpp"
#include "mylib/camera.hpp"
#include "mylib/renderer.hpp"


/* Game constructor. Initializes the window width and height and GLFW itself. */
Game::Game(const unsigned int &windowWidth, const unsigned int &windowHeight) : gameWindow {new Window(windowWidth, windowHeight)} {}

/* Starts the game by initializing GLFW and the window, and then running it. */
void Game::startGame()
{
    glfwInit();
    gameWindow->initWindow("Minecraft");
    gameWindow->makeContextCurrent();
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        std::cerr << "ERROR: Failed to initialize GLAD\n"; 
    glViewport(0, 0, gameWindow->screenWidth, gameWindow->screenHeight);
    return runGame();
}

/* Executes the game. */  
void Game::runGame()
{
    double deltaTime {0.0f}; // Time between current frame and last frame
    double lastFrame {0.0f}; // Time of last frame

    auto renderer = std::make_unique<Renderer>(gameWindow.get());
    auto playerCamera = std::make_unique<Camera>(-90.0f, 0.0f, 2.5f, 0.1f, 45.0f);
    auto dirtBlock = std::make_unique<Block>(SubTextures::GRASS_BLOCK); 

    glEnable(GL_DEPTH_TEST);
    
    // Main game loop
    while (!glfwWindowShouldClose(gameWindow->getWindow()))
    {
        const double currentTime {glfwGetTime()};
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        glClearColor(0.0f, 0.85f, 1.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer->drawChunk(Block(*dirtBlock));

        glfwSwapBuffers(gameWindow->getWindow()); // Swap color buffer

        // Checks if any events are triggered (like keyboard input, etc)
        glfwPollEvents(); 
        playerCamera->updateCameraPos(gameWindow->getWindow());
        renderer->shader->setMat4("view", playerCamera->view);
        gameWindow->processKeyboardInput(deltaTime, playerCamera.get());
    }

    // Destroy objects we no longer need them
    dirtBlock->~Block();
    renderer->~Renderer();
    gameWindow->~Window();
    glfwTerminate();
}

