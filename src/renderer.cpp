#include "minecraft/renderer.hpp"
#include "minecraft/window.hpp"
#include "minecraft/vertices.hpp"
#include "minecraft/buffer.hpp"
#include "minecraft/audio/sound.hpp"

static constexpr float strideToNextBlock {0.5f};
const glm::mat4 Renderer::projection {[]{
        constexpr double fov {glm::radians(45.0)};
        constexpr double aspectRatio {Window::width/Window::height}; 
        constexpr double near {0.1};
        constexpr double far {100.0};
        return glm::perspective(fov, aspectRatio, near, far);
    }()
};

/**
 * Initializes the shaders, blocks and their positions, as well as the 
 * vertex buffer data.
 */
Renderer::Renderer() noexcept : 
playerCamera {[this](){
    constexpr float yaw {90.0f}, pitch {0.0f}, sensitivity {0.1f};
    return Camera{CameraSettings{yaw, pitch, sensitivity}};
}()},
cubeShader {"shaders/block/blockvertexshader.vert", "shaders/block/blockfragmentshader.frag"},
lightSource {[this]() {
    constexpr glm::vec3 ambient {0.25f, 0.25f, 0.25f};
    constexpr glm::vec3 specular {1.0f, 1.0f, 1.0f};
    constexpr glm::vec3 diffuse {0.7f, 0.7f, 0.7f};
    constexpr LightComponents components {ambient, specular, diffuse};

    constexpr glm::vec3 direction {-1.0f, -3.0f, -1.0f};
    constexpr glm::vec3 position {1.0f, 3.0f, 1.0f};
    return Lighting{components, direction, position};
}()}
{
    
    // Create vertex array and bind for the upcoming vertex buffer
    glGenVertexArrays(1, &blockVao);
    glBindVertexArray(blockVao);

    // Create vertex buffer
    constexpr size_t positionOffset {3}, textureOffset {2}, lightDirectionOffset {3};
    BufferData buf {sizeof(cubeVertices), static_cast<const float*>(cubeVertices)};
    vertexBuffer = Buffer::createVertexBuffer(buf, std::vector<size_t>{positionOffset, textureOffset, lightDirectionOffset});

    glm::mat3 normalMatrix {glm::transpose(glm::inverse(glm::mat4(1.0f)))}; // No idea what this does yet..
    cubeShader.useShader(); 
    cubeShader.setMat3("normalMatrix", normalMatrix);
    cubeShader.setVec3("viewPos", playerCamera.cameraPos);
    lightSource.shaderProgramLightSource(cubeShader);

    cubeShader.setInt("allTextures", 0);
    cubeShader.setMat4("projection", projection);

    // Same process again... for the light cubeShader (Don't need this right now since it is a directional light at the moment)
    #if 0
        Lighting::bindLightVAO();
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // Do not need to store the buffer data into it, since we already did it for the cube
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    
        lightSource->lightShader.useShader();
        lightSource->lightShader.setMat4("projection", proj);
    #endif
}

/**
 * Eliminates the positional light source and deletes
 * the vertex buffer and vertex array.
 */
Renderer::~Renderer() noexcept
{
    lightSource.removeAllLights();
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &blockVao);
}


/**
 * Returns true if the block located at 'blockCoords' intersects with the 
 * camera ray. 
 */
bool Renderer::canHighlightBlock(const glm::vec3 &blockCoords) const noexcept
{
    const float distance {glm::distance(blockCoords, playerCamera.cameraPos)};
    constexpr float playerReachableDistance {2.0f};
    if (distance <= playerReachableDistance)
    {
        if (playerCamera.ray.intersectsWith(blockCoords))
        {
            const float distanceBetween {glm::distance(playerCamera.ray.getRay(), blockCoords)};
            const float nextBlock {glm::distance(playerCamera.ray.getRay(), 
                                   glm::vec3{blockCoords.x, blockCoords.y, blockCoords.z + strideToNextBlock})};

            return (distanceBetween <= strideToNextBlock && distanceBetween <= nextBlock);
        }
    }
    return false;
}

/** 
 * Takes the indice of the block in the vector
 * and draws or destroys it.
 */
void Renderer::drawBlock(size_t i) noexcept
{
    float ambient {blocks[i].ambient};
    if (canHighlightBlock(blocks[i].position))
    {
        static int oldState = GLFW_RELEASE;
        const int newState = glfwGetMouseButton(Window::window, GLFW_MOUSE_BUTTON_RIGHT);
        ambient = 1.8f;

        // Destroy the block player is facing
        if (glfwGetMouseButton(Window::window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            Sound::playBlockBreakSound(blocks[i].getSoundID());
            blocks.erase(blocks.begin() + i);
            return;
        }
        // Place a block
        else if (newState == GLFW_RELEASE && oldState == GLFW_PRESS)
        {
            constexpr bool playSFX = true;
            blocks.emplace_back(Block{BlockName::Cobblestone_Block, playSFX, blocks[i].position + glm::vec3{0.0f, 1.0f, 0.0f}});
        }
        oldState = newState;
    }
    glm::mat4 model {glm::translate(glm::mat4{1.0f}, blocks[i].position)};
    cubeShader.setMat4("model", model);
    cubeShader.setFloat("material.ambient", ambient);
    cubeShader.setFloat("textureY", blocks[i].getTextureID());

    constexpr uint8_t verticesToBeDrawn {36};
    return glDrawArrays(GL_TRIANGLES, 0, verticesToBeDrawn);
}

/**
 * Draws all of the blocks available in the block vector. 
 * This will at some point be replaced by something else
 * as rendering dynamically creating thousands of blocks
 * at runtime is too expensive. But suffices for testing
 * purposes.
 */
void Renderer::drawAllBlocks() noexcept
{
    for (size_t i {}; i < blocks.size(); i++)
        drawBlock(i);
}

/**
 * Draws the source of the light, should only be 
 * used for debugging or testing. It does not make 
 * sense to draw the light source since it is a directional light. 
 */
void Renderer::drawLightSource() noexcept
{
    Lighting::bindLightVAO();
    lightSource.lightShader.useShader();
    glm::mat4 model {glm::translate(glm::mat4{1.0f}, lightSource.position)};
    lightSource.lightShader.setMat4("model", model);
    // glDrawArrays(GL_TRIANGLES, 0, 36);
}

/**
 * Updates the camera view for the player, 
 * and updates all the shaders to the updated 
 * position of the camera. 
 */
void Renderer::updateView() noexcept
{
    double xPos, yPos;
    glfwGetCursorPos(Window::window, &xPos, &yPos);
    playerCamera.updateCameraPos(xPos, yPos);
    cubeShader.setMat4("view", playerCamera.getView());
    cubeShader.setVec3("viewPos", playerCamera.cameraPos);
    #if 0
        lightSource->lightShader.useShader();
        lightSource->lightShader.setMat4("view", playerCamera.view);
    #endif
}

