#include "GLFW/glfw3.h"
#include "minecraft/camera.hpp"
#include "minecraft/window.hpp"


/** 
 * Initializes the scalar values such as yaw, pitch, speed, sensitivity, and zoom.
 * The other members are automatically initialized upon construction. 
 */  
Camera::Camera(const CameraSettings &cameraSettings) :
settings {cameraSettings},
cameraRight {glm::normalize(glm::cross(cameraFront, cameraUp)) * settings.speed} 
{
    double xPos {}, yPos {};
	glfwGetCursorPos(Window::getWindow(), &xPos, &yPos);
    
}


/** 
 * Updates the position of where the camera is looking.
 */
void Camera::updateCameraPos()
{
	const float cosPitch {cosf(glm::radians(settings.pitch))};

    // Calculate a 3D vector given the yaw and pitch
	glm::vec3 direction {
        cosf(glm::radians(settings.yaw)) * cosPitch,
        sinf(glm::radians(settings.pitch)),
        sinf(glm::radians(settings.yaw)) * cosPitch
    };

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
	cameraFront = glm::normalize(direction);

	double xPos {}, yPos {};
    static double lastX {}, lastY {};
    static bool firstMouseMovement = true;

	glfwGetCursorPos(Window::getWindow(), &xPos, &yPos);

    if (firstMouseMovement)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouseMovement = false;
    }

    const float xOffset {static_cast<float>((xPos - lastX)) * settings.sensitivity};
    const float yOffset {static_cast<float>((lastY - yPos)) * settings.sensitivity}; // y-axis is reversed, which is why the order is flipped

    // Update the last mouse positions to the current position
    lastX = xPos;
    lastY = yPos;

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


    cameraRay.origin = cameraPos;
    cameraRay.direction = cameraFront;
    #if 1
        cameraRay.updateRay();
    #endif

}