#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "mylib/game.hpp"
#include "mylib/camera.hpp"
#include "mylib/renderer.hpp"
#include "mylib/lighting.hpp"
#include "mylib/glerror.hpp"


/* Game constructor. Initializes the window width and height and GLFW itself. */
Game::Game(uint16_t windowWidth, uint16_t windowHeight) 
{
    glfwInit();
    Window::initWindow("Minecraft", windowWidth, windowHeight);
    glfwMakeContextCurrent(Window::glfwWindow);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        GLError::error_message("Failed to initialize GLAD");

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
    while (!glfwWindowShouldClose(Window::glfwWindow))
    {
        const float currentTime {static_cast<float>(glfwGetTime())};
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        glClearColor(0.0f, 0.8f, 1.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer->updateView();
        renderer->drawBlock({0.0f, 0.0f, 0.0f});

        glfwSwapBuffers(Window::glfwWindow); // Swap color buffer

        // Checks if any events are triggered (like keyboard input, etc)
        glfwPollEvents(); 
        Window::processKeyboardInput(deltaTime, renderer->playerCamera.get());
    }
    
}

Game::~Game()
{
    Window::destroyWindow();
    glfwTerminate();
}

