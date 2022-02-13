#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include "mylib/game.hpp"
#include "mylib/camera.hpp"
#include "mylib/renderer.hpp"
#include "mylib/lighting.hpp"


/* Game constructor. Initializes the window width and height and GLFW itself. */
Game::Game(unsigned int windowWidth, unsigned int windowHeight) 
{
    glfwInit();
    initWindow("Minecraft", windowWidth, windowHeight);
    glfwMakeContextCurrent(glfwWindow);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        std::cerr << "ERROR: Failed to initialize GLAD\n"; 
    glViewport(0, 0, windowWidth, windowHeight);
    Lighting::initLightVAO();
    Renderer::initProjection();
}

/* Executes the game. */  
void Game::runGame()
{
    float deltaTime {0.0f}; // Time between current frame and last frame
    float lastFrame {0.0f}; // Time of last frame

    auto renderer = std::make_unique<Renderer>();

    glEnable(GL_DEPTH_TEST);
    
    // Main game loop
    while (!glfwWindowShouldClose(glfwWindow))
    {
        const float currentTime {static_cast<float>(glfwGetTime())};
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        glClearColor(0.0f, 0.8f, 1.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer->updateView();
        renderer->drawBlock({0.0f, 0.0f, 0.0f});

        glfwSwapBuffers(glfwWindow); // Swap color buffer

        // Checks if any events are triggered (like keyboard input, etc)
        glfwPollEvents(); 
        processKeyboardInput(deltaTime, renderer->playerCamera.get());
    }
    
}

Game::~Game()
{
    destroyWindow();
    glfwTerminate();
}

