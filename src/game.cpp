#define GLFW_INCLUDE_NONE
#define GAME_BENCHMARK

#include <cmath>

#include "minecraft/game/game.hpp"
#include "minecraft/rendering/renderer.hpp"
#include "minecraft/glerror/glerror.hpp"
#include "minecraft/window/window.hpp"
#include "minecraft/gfx/texture.hpp"
#ifdef GAME_BENCHMARK
    #include "misc/timer.hpp"
#endif
#include "minecraft/math/glmath.hpp"
#include "minecraft/world/worldgen.hpp"

static GLuint uniformBuffer;
static GLuint vao;

#ifndef NDEBUG
    /**
     * Returns true if the debug output context
     * was successfully initialized.
     */
    static bool initializedDebugContext() noexcept
    {
        static constexpr int DEBUG_CONTEXT_INITIALIZATION_FAILURE {0};
        int flag {};
        glGetIntegerv(GL_CONTEXT_FLAGS, &flag);
        return ((flag & GL_CONTEXT_FLAG_DEBUG_BIT) != DEBUG_CONTEXT_INITIALIZATION_FAILURE);
    }
#endif


/**
 * Called upon the game's initialization.
 * Should be one of the first methods called
 * in the main function.
 */
void initGame(const char *windowTitle) noexcept
{
    glfwInit();
    WorldGen::initSeed();
    Window::initWindow(windowTitle);
    glfwMakeContextCurrent(Window::getWindow());
    
    static constexpr int GLAD_INITIALIZATION_FAILURE {0};
    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == GLAD_INITIALIZATION_FAILURE)
        GLError::error_message("Failed to initialize GLAD");
    
    // Check if initializing the debug context was successful (if on a debug build)
    #ifndef NDEBUG
        printf("Running on debug build.\n");
        if (!initializedDebugContext()) {
            GLError::error_message("Failed to initialize OpenGL debug context");
}
        GLError::enableGLDebugCallBack();
    #endif

    static constexpr float x {};
    static constexpr float y {};
    glViewport(x, y, Window::WIDTH, Window::HEIGHT);

    // Initialize vertex array for uniform buffer
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Initialize uniform buffer, bind it, and store the data
    glGenBuffers(1, &uniformBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer);

    // Allocate enough space before filling in the buffer
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), nullptr, GL_STATIC_DRAW); 

    // Fill in the buffer's data
    static constexpr int BINDING_POINT {0};
    static constexpr int OFFSET {0};
    glBindBufferRange(GL_UNIFORM_BUFFER, BINDING_POINT, uniformBuffer, OFFSET, sizeof(glm::mat4));
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &GLMath::PROJECTION[0][0]);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

static inline void updateCamera(const Renderer &renderer) noexcept
{
    double mouseXPos {};
    double mouseYPos {};
    glfwGetCursorPos(Window::getWindow(), &mouseXPos, &mouseYPos);
    Camera::updateCameraPos();
    renderer.getShader().useShader();
    renderer.getShader().setMat4("view", Camera::getView());
    renderer.getShader().setVec3("viewPos", Camera::cameraPos);
    renderer.getShader().setFloat("iTime", static_cast<float>(glfwGetTime()));
}

/**
 * Executes the game through an
 * infinite loop until the program
 * is terminated.
 */  
void runGame() noexcept
{
    float lastFrame {0.0F}; // Time of last frame

    const Texture textureAtlas {"./textures/textureatlas.png"};
    Renderer renderer;
    #ifdef GAME_BENCHMARK
        Timer<std::milli> time;
    #endif

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // RGB constants for the game's background colors (including alpha)
    static constexpr float RED {0.0F};
    static constexpr float GREEN {0.8F};
    static constexpr float BLUE {1.0F};
    static constexpr float ALPHA {1.0F}; 
    glClearColor(RED, GREEN, BLUE, ALPHA);

    renderer.getShader().setVec2("iResolution", glm::vec2{Window::WIDTH, Window::HEIGHT});

    // Main game loop
    static constexpr int WINDOW_NOT_CLOSED {0};
    while (glfwWindowShouldClose(Window::getWindow()) == WINDOW_NOT_CLOSED)
    {
        #ifdef GAME_BENCHMARK
            time.start();
        #endif
        const float currentTime {static_cast<float>(glfwGetTime())};
        const float deltaTime {currentTime - lastFrame};
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
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &uniformBuffer);
    Window::deleteWindow();
    #ifdef GAME_BENCHMARK
        time.detailedDisplay();
    #endif
}
