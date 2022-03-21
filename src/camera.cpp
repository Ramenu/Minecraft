#include "minecraft/camera.hpp"


/** 
 * Updates the position of where the camera is looking.
 * Parameters take the position of the mouse's 
 * x-position and y-position.
 */
void Camera::updateCameraPos(const double cursorX, const double cursorY) noexcept
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
    static bool firstMouseMovement = true;

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
        constexpr float angle180 {180.0f}; 
        constexpr float angle360 {360.0f};

        // Prevent the player tilting their head backwards
        if (settings.pitch > angle180)
            settings.pitch = angle180;
        else if (settings.pitch < -angle180)
            settings.pitch = -angle180;
        
        // Reset the yaw so the player can spin their camera around 
        if (settings.yaw > angle360)
            settings.yaw = 0.0f;
        else if (settings.yaw < -angle360)
            settings.yaw = 0.0f;
    #endif

    #if 1
        ray.updateRay(cameraPos, direction.front);
    #endif

}