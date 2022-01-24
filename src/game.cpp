#define GLFW_INCLUDE_NONE
#define LENGTHOF(a) sizeof(a)/sizeof(*a)

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include "mylib/game.hpp"
#include "mylib/camera.hpp"
#include "mylib/renderer.hpp"
#include "mylib/lighting.hpp"


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
    Lighting::initLightVAO();
    return runGame();
}

/* Executes the game. */  
void Game::runGame()
{
    double deltaTime {0.0f}; // Time between current frame and last frame
    double lastFrame {0.0f}; // Time of last frame

    auto renderer = std::make_unique<Renderer>(gameWindow.get());
    auto dirtBlock = std::make_unique<Block>(SubTextures::GRASS_BLOCK); 

    glEnable(GL_DEPTH_TEST);
    
    // Main game loop
    while (!glfwWindowShouldClose(gameWindow->getWindow()))
    {
        const double currentTime {glfwGetTime()};
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        glClearColor(0.0f, 0.8f, 1.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer->drawLightSource();
        renderer->drawChunk(Block(*dirtBlock));
        //renderer->drawBlock(Block(*dirtBlock), {2.0f, 0.0f, 0.0f});

        glfwSwapBuffers(gameWindow->getWindow()); // Swap color buffer

        // Checks if any events are triggered (like keyboard input, etc)
        glfwPollEvents(); 
        renderer->updateView(gameWindow->getWindow());
        gameWindow->processKeyboardInput(deltaTime, renderer->playerCamera.get());
    }
    
    glfwTerminate();
}

Game::~Game()
{
    
}

