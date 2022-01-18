#define GLFW_INCLUDE_NONE
#define LENGTHOF(a) sizeof(a)/sizeof(*a)

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <stb-master/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "mylib/graphics/shader.hpp"
#include "mylib/game.hpp"
#include "mylib/attribute.hpp"
#include "mylib/buffers/buffer.hpp"
#include "mylib/vertices.hpp"
#include "mylib/graphics/textures.hpp"
#include "mylib/block.hpp"
#include "mylib/camera.hpp"


/* Game constructor. Initializes the window width and height and GLFW itself. */
Game::Game(const unsigned int &windowWidth, const unsigned int &windowHeight) : gameWindow(windowWidth, windowHeight) {}

/* Starts the game by initializing GLFW and the window, and then running it. */
void Game::startGame()
{
    glfwInit();
    gameWindow.initWindow("Minecraft");
    gameWindow.makeContextCurrent();
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        std::cerr << "ERROR: Failed to initialize GLAD\n"; 
    glViewport(0, 0, gameWindow.screenWidth, gameWindow.screenHeight);
    return runGame();
}

/* Executes the game. */  
void Game::runGame()
{
    double deltaTime {0.0f}; // Time between current frame and last frame
    double lastFrame {0.0f}; // Time of last frame

    const char* vertexShaderFilePath {"shaders/vertexshader.vs"};
    const char* fragmentShaderFilePath {"shaders/fragmentshader.fs"};

    // Create and load our shaders
    Shader basicShader;
    basicShader.loadShaders(vertexShaderFilePath, fragmentShaderFilePath);
    
    // Create our buffers and store the attribute data in them
    unsigned int vao, vertexBuffer;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vertexBuffer);
    glBindVertexArray(vao);
    loadVertexBuffer(vertexBuffer, sizeof(cubeVertices), cubeVertices);
    setAttributes(3, 2);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    stbi_set_flip_vertically_on_load(true); // Flip loaded textures on the y-axis

    basicShader.useShader(); // Use the shader program

    auto dirtBlock {std::make_unique<Block>("textures/grassblock")};
    
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), static_cast<float>(gameWindow.screenWidth) / static_cast<float>(gameWindow.screenHeight), 0.1f, 100.0f);
    basicShader.setMat4("projection", proj);
    glEnable(GL_DEPTH_TEST);
    
    // Main game loop
    while (!glfwWindowShouldClose(gameWindow.getWindow()))
    {
        const double currentTime {glfwGetTime()};
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        glClearColor(0.0f, 0.85f, 1.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (unsigned int i {}; i < 10; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(i, 0.0f, 0.0f));
            basicShader.setMat4("model", model);
            dirtBlock->drawBlock();
            for (unsigned int j {}; j < 5; j++)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(i, 0.0f, j));
                basicShader.setMat4("model", model);
                dirtBlock->drawBlock();
            }
        }

        glfwSwapBuffers(gameWindow.getWindow()); // Swap color buffer

        // Checks if any events are triggered (like keyboard input, etc)
        glfwPollEvents(); 
        playerCamera->updateCameraPos();
        basicShader.setMat4("view", playerCamera->view);
        gameWindow.processKeyMovement(deltaTime);
    }

    // Destroy objects and buffers once we no longer need them
    delete(&playerCamera);
    dirtBlock->~Block();
	basicShader.deleteShaderProgram();
    glDeleteBuffers(1, &vertexBuffer);
    glfwTerminate();
}

