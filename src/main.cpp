#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include "mylib/window.h"
#include "mylib/vertices.h"
#include "mylib/shader.h"
#include "mylib/textures.h"
#include "mylib/camera.h"
#include <iostream>
#include <vector>
#include <fstream>

//g++ -g -std=c++17 -I./include -L./lib  src/main.cpp src/glad.c src/window.cpp src/shader.cpp src/vertices.cpp src/textures.cpp src/camera.cpp -o main -lglfw3dll
int main()
{

    glfwInit(); //Initialize GLFW
    Window wind; 
    Shader shad;
    Textures text;

    //Initialize deltaTime and lastFrame to 0
    float deltaTime {0.0f};
    float lastFrame {0.0f};

    wind.screenHeight = 600; wind.screenWidth = 600; //Initialize the screen height and width

    wind.wireFrameMode = false;
    //Initialize the mouse positions in the center of the screen
    float lastX = wind.screenHeight / 2.0;
    float lastY = wind.screenWidth / 2.0; 
    
    GLFWwindow* window = wind.loadWindow(window, "Minecraft"); //Load window into loadWindow method
    glfwMakeContextCurrent(window); //Makes the context of the specified window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback); //Insert our mouse callback method into GLFW
    glfwSetMouseButtonCallback(window, on_Mouse_Button);

    //If GLAD fails to initialize for whatever reason
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initalize GLAD\n";
        return -1;
    }
    //Create our buffers, and VAO
    unsigned int vertexBuffer, vertexArray, elementBuffer;
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &elementBuffer);
    glGenVertexArrays(1, &vertexArray);

    glBindVertexArray(vertexArray); //Bind vertex array before binding vertex buffer

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Store vertices data into the buffer

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //Store the indices into the element buffer

    shad.loadShaders("shaders/vertexshader.vs", "shaders/fragmentshader.fs"); //Call to load shaders to automatically load the shaders

    //Pointer to the vertices coordinate attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind the buffer

    //Set up our textures
    unsigned int grassBlockTexture, grassBlockTopTexture, dirtBlock;
    glGenTextures(1, &grassBlockTexture);
    glGenTextures(1, &grassBlockTopTexture);
    glGenTextures(1, &dirtBlock);

    stbi_set_flip_vertically_on_load(true); //Since openGL axis is flipped, flip vertically is set to true

    //Bind the appropriate textures and load them into openGL
    glBindTexture(GL_TEXTURE_2D, grassBlockTopTexture); 
    text.set_Default_2D_Texture_Configs();
    text.loadTexture("include/textures/grass_block_top.jpg", true);

    glBindTexture(GL_TEXTURE_2D, grassBlockTexture);
    text.set_Default_2D_Texture_Configs();
    text.loadTexture("include/textures/grass_block.jpg", true);

    glBindTexture(GL_TEXTURE_2D, dirtBlock);
    text.set_Default_2D_Texture_Configs();
    text.loadTexture("include/textures/dirt_block.jpg", true);

    unsigned int grassBlockTextures[3] {grassBlockTopTexture, grassBlockTexture, dirtBlock};
    shad.passTexturesToShaders(grassBlockTextures[0], grassBlockTextures[1], grassBlockTextures[2]);
    glEnable(GL_DEPTH_TEST);
    
    bool printCoords {true};

    //While the window is kept running
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime(); //Initialize the current frame
        deltaTime = currentFrame - lastFrame; //deltaTime calculates the amount of time between the last frame and the current frame
        lastFrame = currentFrame; //Update the last frame

        //Call the key_callback method that contains the inputs
        wind.key_callback(window, deltaTime);

        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f); //Initialize the identity matrix
       

        /*The lookAt matrix transforms all the world coordinates to the view space we just defined.. GLM does this work for us
          Just specify the:
          - Camera position
          - Target position
          - Vector that represents the up in world space*/
        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        shad.useShader(); //Use our shader program

        glm::mat4 projection = glm::mat4(1.0f); //Initialize the projection matrix
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f)); //Set where we want to rotate our model
        projection =  glm::perspective(glm::radians(45.0f), (float)wind.screenWidth / (float)wind.screenHeight, 0.1f, 100.0f); //Set perspective
        //Reference the uniform locations
        int modelLocation = glGetUniformLocation(shad.shaderProgram, "model");
        int viewLocation = glGetUniformLocation(shad.shaderProgram, "view");
        
        //Tells GLM our matrix locations inside GLSL
        //shad.setMat4("model", model);
        shad.setMat4("view", view);
        shad.setMat4("projection", projection);

        glBindVertexArray(vertexArray); //Bind array
        //shad.translateAndDrawBlock(grassBlockPositions[0]);
        shad.loadVertexData(grassBlockPositions);
        if (cameraPos.x > grassBlockPositions[6].x)
        {
            grassBlockPositions.push_back(glm::vec3{cameraPos.x, cameraPos.y - 2.0f, cameraPos.z});
        }

        //Swap colour buffers and checks if events are triggered
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
