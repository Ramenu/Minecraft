#include "GLFW/glfw3.h"
#include "mylib/camera.hpp"


/* Constructor for Camera class. */
Camera::Camera(const float& yaw, const float& pitch, const float& movementSpeed, const float& mouseSensitivity, const float& zoom) : 
   cameraPos {glm::vec3(0.0f, 0.0f, 3.0f)}, cameraFront {glm::vec3(0.0f, 0.0f, -1.0f)}, cameraRight {glm::normalize(glm::cross(cameraFront, cameraUp)) * movementSpeed},
   view {glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp)}, movementSpeed {movementSpeed}, deltaTime {0.0f}, lastFrame {0.0f}, 
   yaw {yaw}, pitch {pitch}, mouseSensitivity {mouseSensitivity}, zoom {zoom}, firstMouseMovement {true}, lastX {}, lastY {}, cameraUp {glm::vec3(0.0f, 1.0f, 0.0f)}  {}


/* Camera class destructor. */
Camera::~Camera()
{

}

/* Updates the position of the camera. */
void Camera::updateCameraPos(GLFWwindow* window)
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
    int width, height;

	glfwGetCursorPos(window, &xPos, &yPos);
    glfwGetWindowSize(window, &width, &height);

    // To prevent cursor from going out of screen range
    if (xPos > width)
        glfwSetCursorPos(window, width - 1, yPos);
    else if (xPos < 0)
        glfwSetCursorPos(window, 0, yPos + 1);
    if (yPos > height)
        glfwSetCursorPos(window, xPos, height - 1);
    else if (yPos < -30) // Limit kept at -30 so the user can still minimize/fullscreen or close the game
        glfwSetCursorPos(window, xPos, -29);


    if (firstMouseMovement)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouseMovement = false;
    }

    double xOffset {xPos - lastX};
    double yOffset {lastY - yPos}; // y-axis is reversed, which is why the order is flipped

    // Update the last mouse positions to the current position
    lastX = xPos;
    lastY = yPos;

    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    // To prevent the player from turning past a certain angle
    if (pitch > 180.0f)
        pitch = 180.0f;
    else if (pitch < -180.0f)
        pitch = -180.0f;

}