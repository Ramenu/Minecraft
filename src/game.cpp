#define GLFW_INCLUDE_NONE
#define GAME_BENCHMARK

#include "minecraft/game/game.hpp"
#include "minecraft/rendering/renderer.hpp"
#include "minecraft/glerror/glerror.hpp"
#include "minecraft/window/window.hpp"
#include "minecraft/gfx/texture.hpp"
#ifdef GAME_BENCHMARK
    #include "misc/timer.hpp"
#endif

static GLuint uniformBuffer;

/**
 * Returns true if the debug output context
 * was successfully initialized.
 */
static bool initializedDebugContext() noexcept
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
    glfwMakeContextCurrent(Window::getWindow());
    
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        GLError::error_message("Failed to initialize GLAD");
    
    // Check if initializing the debug context was successful (if on a debug build)
    #ifdef MC_DEBUG_BUILD
        if (!initializedDebugContext())
            GLError::error_message("Failed to initialize OpenGL debug context");
        GLError::enableGLDebugCallBack();
    #endif

    static constexpr float x {}, y {};
    glViewport(x, y, Window::width, Window::height);
    Lighting::initLightVAO();

    // Initialize uniform buffer, bind it, and store the data
    glGenBuffers(1, &uniformBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer);

    const glm::mat3 normalMatrix {glm::transpose(glm::inverse(glm::mat4(1.0f)))}; // No idea what this does yet..

    // Allocate enough space before filling in the buffer
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) + sizeof(glm::mat3), nullptr, GL_STATIC_DRAW); 

    // Fill in the buffer's data
    static constexpr size_t bindingPoint {0}, offset {0};
    glBindBufferRange(GL_UNIFORM_BUFFER, bindingPoint, uniformBuffer, offset, sizeof(glm::mat4) + sizeof(glm::mat3));
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &projection[0][0]);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat3), &normalMatrix[0][0]);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

static inline void updateCamera(const Renderer &renderer) noexcept
{
    double mouseXPos, mouseYPos;
    glfwGetCursorPos(Window::getWindow(), &mouseXPos, &mouseYPos);
    Camera::updateCameraPos();
    renderer.cubeShader.setMat4("view", Camera::getView());
    renderer.cubeShader.setVec3("viewPos", Camera::cameraPos);
}

/**
 * Executes the game through an
 * infinite loop until the program
 * is terminated.
 */  
void runGame() noexcept
{
    [[maybe_unused]] float deltaTime {0.0f}; // Time between current frame and last frame
    float lastFrame {0.0f}; // Time of last frame

    Texture textureAtlas {"./textures/textureatlas.jpg"};
    Renderer renderer;
    #ifdef GAME_BENCHMARK
        Timer<std::milli> time;
    #endif
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // RGB constants for the game's background colors (including alpha)
    static constexpr float red {0.0f}, green {0.8f}, blue {1.0f}, alpha {1.0f}; 
    glClearColor(red, green, blue, alpha);
    
    // Main game loop
    while (!glfwWindowShouldClose(Window::getWindow()))
    {
        #ifdef GAME_BENCHMARK
            time.start();
        #endif
        const float currentTime {static_cast<float>(glfwGetTime())};
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        updateCamera(renderer);
        renderer.draw();

        glfwSwapBuffers(Window::getWindow()); // Swap color buffer
        
        // Checks if any events are triggered (like keyboard input, etc)
        glfwPollEvents(); 
        renderer.update();
        Window::processMovement(deltaTime);
        #ifdef GAME_BENCHMARK
            time.end();
        #endif
    }

    // Free up remaining resources used by the game
    glDeleteBuffers(1, &uniformBuffer);
    glfwTerminate();
    #ifdef GAME_BENCHMARK
        time.detailedDisplay();
    #endif
}
