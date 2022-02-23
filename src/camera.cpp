#include "GLFW/glfw3.h"
#include "mylib/camera.hpp"
#include "mylib/window.hpp"


/* Initializes the scalar values such as yaw, pitch, speed, sensitivity, and zoom.
   The other members are automatically initialized upon construction. */
Camera::Camera(float cameraYaw, float cameraPitch, 
               float cameraSpeed, float cameraSensitivity, float cameraZoom) :
yaw {cameraYaw}, 
pitch {cameraPitch}, 
movementSpeed {cameraSpeed}, 
mouseSensitivity {cameraSensitivity}, 
zoom {cameraZoom}{}


/* Updates the position of the camera. */
void Camera::updateCameraPos()
{
	glm::vec3 direction;
	const double cosPitch {cos(glm::radians(pitch))};

    // Calculate a 3D vector given the yaw and pitch
	direction.x = cos(glm::radians(yaw)) * cosPitch;
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cosPitch;
    
    	
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
	cameraFront = glm::normalize(direction);

	double xPos, yPos;
	glfwGetCursorPos(Window::getWindow(), &xPos, &yPos);

    if (firstMouseMovement)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouseMovement = false;
    }

    float xOffset {static_cast<float>(xPos - lastX)};
    float yOffset {static_cast<float>(lastY - yPos)}; // y-axis is reversed, which is why the order is flipped

    // Update the last mouse positions to the current position
    lastX = xPos;
    lastY = yPos;

    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    #if 1
        // To prevent the player from turning past a certain angle
        if (pitch > 180.0f)
            pitch = 180.0f;
        else if (pitch < -180.0f)
            pitch = -180.0f;
    #endif


    cameraRay.origin = cameraPos;
    cameraRay.direction = cameraFront;
    #if 1
        cameraRay.drawRay();
    #endif

}