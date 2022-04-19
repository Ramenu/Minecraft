#include "minecraft/camera/camera.hpp"

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
        const float cosPitch {cosf(glm::radians(settings.pitch))};

        // Calculate a 3D vector given the yaw and pitch
        glm::vec3 updatedDirection {
            cosf(glm::radians(settings.yaw)) * cosPitch,
            sinf(glm::radians(settings.pitch)),
            sinf(glm::radians(settings.yaw)) * cosPitch
        };

        view = glm::lookAt(cameraPos, cameraPos + direction.front, up);
        direction.right = glm::normalize(glm::cross(direction.front, up));
        direction.front = glm::normalize(updatedDirection);

        static double lastX {}, lastY {};
        static bool firstMouseMovement {true};

        if (firstMouseMovement)
        {
            lastX = cursorX;
            lastY = cursorY;
            firstMouseMovement = false;
        }

        const float xOffset {static_cast<float>((cursorX - lastX)) * settings.sensitivity};
        const float yOffset {static_cast<float>((lastY - cursorY)) * settings.sensitivity}; // y-axis is reversed, which is why the order is flipped

        // Update the last mouse positions to the current position
        lastX = cursorX;
        lastY = cursorY;

        settings.yaw += xOffset;
        settings.pitch += yOffset;

        #if 1
            // Angles in degrees
            static constexpr float upDownTurnAngle {88.0f}; 
            static constexpr float sideTurnAngle {360.0f};

            // Prevent the player tilting their head backwards
            if (settings.pitch > upDownTurnAngle)
                settings.pitch = upDownTurnAngle;
            else if (settings.pitch < -upDownTurnAngle)
                settings.pitch = -upDownTurnAngle;
            
            // Reset the yaw so the player can spin their camera around 
            if (settings.yaw > sideTurnAngle)
                settings.yaw = 0.0f;
            else if (settings.yaw < -sideTurnAngle)
                settings.yaw = 0.0f;
        #endif

        #if 1
            ray.updateRay(cameraPos, direction.front);
        #endif

    }
}