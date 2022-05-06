#include "minecraft/camera/camera.hpp"
#include "minecraft/math/glmath.hpp"

namespace Camera
{
    static glm::mat4 view;
    glm::mat4 getView() noexcept {return view;}

    /** 
     * Updates the position of where the camera is looking.
     * Parameters take the position of the mouse's 
     * x-position and y-position.
     */
    void updateCameraPos(const double cursorX, const double cursorY) noexcept
    {
        const float yawRadians {glm::radians(settings.yaw)}, pitchRadians {glm::radians(settings.pitch)};
        const float cosPitch {std::cos(pitchRadians)};

        // Calculate a 3D vector given the yaw and pitch
        const glm::vec3 updatedDirection {
            std::cos(yawRadians) * cosPitch,
            std::sin(pitchRadians),
            std::sin(yawRadians) * cosPitch
        };

        view = glm::lookAt(cameraPos, cameraPos + direction.front, up);
        direction.right = glm::normalize(glm::cross(direction.front, up));
        direction.front = glm::normalize(updatedDirection);

        static double lastX {cursorX}, lastY {cursorY};

        const float xOffset {static_cast<float>((cursorX - lastX)) * settings.sensitivity};
        const float yOffset {static_cast<float>((lastY - cursorY)) * settings.sensitivity}; // y-axis is reversed, which is why the order is flipped

        // Update the last mouse positions to the current position
        lastX = cursorX;
        lastY = cursorY;

        settings.yaw += xOffset;
        settings.pitch += yOffset;

        // Angles in degrees
        static constexpr float upDownTurnAngle {88.0f}; 
        static constexpr float sideTurnAngle {360.0f};

        // Prevent the player tilting their head backwards
        if (settings.pitch > upDownTurnAngle)
            settings.pitch = upDownTurnAngle;
        if (settings.pitch < -upDownTurnAngle)
            settings.pitch = -upDownTurnAngle;
        
        // Reset the yaw so the player can spin their camera around 
        if (settings.yaw > sideTurnAngle)
            settings.yaw = 0.0f;
        if (settings.yaw < -sideTurnAngle)
            settings.yaw = 0.0f;

        #if 1
            //TODO: When a position is not found by the camera, just get the nearest block instead (provided it is in range)
            const Direction nearestDirectionToPlayer {GLMath::getDirectionClosestTo(direction.front)};
            switch (nearestDirectionToPlayer)
            {
                default: ray.updateRay({cameraPos.x, cameraPos.y, cameraPos.z}, direction.front); break; // Up
                case West: ray.updateRay({cameraPos.x - 1, cameraPos.y, cameraPos.z}, direction.front); break;
                case East: ray.updateRay({cameraPos.x + 1, cameraPos.y, cameraPos.z}, direction.front); break;
                case North: ray.updateRay({cameraPos.x, cameraPos.y, cameraPos.z + 1}, direction.front); break;
                case South: ray.updateRay({cameraPos.x, cameraPos.y, cameraPos.z - 1}, direction.front); break;
                case Down: ray.updateRay({cameraPos.x + 1, cameraPos.y, cameraPos.z}, direction.front); break;
            }
        #endif

    }
}