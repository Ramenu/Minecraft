#include "minecraft/camera/camera.hpp"
#include "minecraft/math/glmath.hpp"
#include "minecraft/window/window.hpp"

namespace Camera
{
    static glm::mat4 view;
    glm::mat4 getView() noexcept {return view;}
    Ray getRay() noexcept {return ray;}

    void initCameraRay(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &)
    {
        //NOTE: GREEN IS YOU!
        ray.initRay({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 3.0f});
        //ray.initRay(cameraPos, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 3.0f});
    }

    /** 
     * Updates the position of where the camera is looking.
     */
    void updateCameraPos() noexcept
    {
        const float yawRadians {glm::radians(settings.yaw)}, pitchRadians {glm::radians(settings.pitch)};
        const float cosPitch {std::cos(pitchRadians)};

        // Calculate a 3D vector given the yaw and pitch
        const glm::vec3 updatedDirection {
            std::cos(yawRadians) * cosPitch,
            std::sin(pitchRadians),
            std::sin(yawRadians) * cosPitch
        };

        view = glm::lookAt(cameraPos, cameraPos + direction.front, UP);
        direction.right = glm::normalize(glm::cross(direction.front, UP));
        direction.front = glm::normalize(updatedDirection);

        double mouseX, mouseY;
        glfwGetCursorPos(Window::getWindow(), &mouseX, &mouseY);
        static double lastX {mouseX}, lastY {mouseY};

        const float xOffset {static_cast<float>(mouseX - lastX) * settings.sensitivity};
        const float yOffset {static_cast<float>(lastY - mouseY) * settings.sensitivity}; // y-axis is reversed, which is why the order is flipped

        // Update the last mouse positions to the current position
        lastX = mouseX;
        lastY = mouseY;

        settings.yaw += xOffset;
        settings.pitch += yOffset;

        // Angles in degrees
        static constexpr float UP_DOWN_TURN_ANGLE {88.0f}; 
        //static constexpr float sideTurnAngle {360.0f};

        // Prevent the player tilting their head backwards
        if (settings.pitch > UP_DOWN_TURN_ANGLE)
            settings.pitch = UP_DOWN_TURN_ANGLE;
        else if (settings.pitch < -UP_DOWN_TURN_ANGLE)
            settings.pitch = -UP_DOWN_TURN_ANGLE;
        
        // Reset the yaw so the player can spin their camera around 
        //if (settings.yaw > sideTurnAngle || settings.yaw < -sideTurnAngle)
        //    settings.yaw = 0.0f;

        //ray.ray = {3.0f, 23.0f, 3.0f};
        ray.ray = cameraPos;
        ray.updateRay(yawRadians, pitchRadians, 0.0f);
        //glfwSetWindowTitle(Window::getWindow(), std::string{std::to_string(ray.getRay().x) + ", " +  std::to_string(ray.getRay().y) + ", " + std::to_string(ray.getRay().z)}.c_str());
        //glfwSetWindowTitle(Window::getWindow(), std::to_string(yawRadians).c_str());

    }
}