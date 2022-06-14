#include "minecraft/camera/camera.hpp"
#include "minecraft/math/glmath.hpp"
#include "minecraft/window/window.hpp"

namespace Camera
{
    static glm::mat4 view;
    static Ray cameraRay;
    glm::mat4 getView() noexcept {return view;}
    Ray getCameraRay() noexcept {return cameraRay;}

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


        view = glm::lookAt(cameraPos, cameraPos + direction.front, CAMERA_UP);
        direction.right = glm::normalize(glm::cross(direction.front, CAMERA_UP));
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
        static constexpr float CAMERA_UP_DOWN_TURN_ANGLE {88.0f}; 
        //static constexpr float sideTurnAngle {360.0f};

        // Prevent the player tilting their head backwards
        if (settings.pitch > CAMERA_UP_DOWN_TURN_ANGLE)
            settings.pitch = CAMERA_UP_DOWN_TURN_ANGLE;
        else if (settings.pitch < -CAMERA_UP_DOWN_TURN_ANGLE)
            settings.pitch = -CAMERA_UP_DOWN_TURN_ANGLE;
        
        // Reset the yaw so the player can spin their camera around 
        //if (settings.yaw > sideTurnAngle || settings.yaw < -sideTurnAngle)
        //    settings.yaw = 0.0f;

         #if 1
            //TODO: When a position is not found by the camera, just get the nearest block instead (provided it is in range)
            const Direction nearestDirectionToPlayer {GLMath::getDirectionClosestTo(direction.front)};
            switch (nearestDirectionToPlayer)
            {
                default: cameraRay.updateRay({cameraPos.x, cameraPos.y, cameraPos.z}, direction.front); break; // Up
                case West: cameraRay.updateRay({cameraPos.x - 1, cameraPos.y, cameraPos.z}, direction.front); break;
                case East: cameraRay.updateRay({cameraPos.x + 1, cameraPos.y, cameraPos.z}, direction.front); break;
                case North: cameraRay.updateRay({cameraPos.x, cameraPos.y, cameraPos.z + 1}, direction.front); break;
                case South: cameraRay.updateRay({cameraPos.x, cameraPos.y, cameraPos.z - 1}, direction.front); break;
                case Down: cameraRay.updateRay({cameraPos.x + 1, cameraPos.y, cameraPos.z}, direction.front); break;
            }
        #endif

    }
}