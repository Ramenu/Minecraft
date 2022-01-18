#include "mylib/camera.hpp"

Camera* playerCamera {new Camera(-90.0f, 0.0f, 2.5f, 0.1f, 45.0f)};

/* Constructor for Camera class. */
Camera::Camera(const float& yaw, const float& pitch, const float& movementSpeed, const float& mouseSensitivity, const float& zoom) : 
   cameraPos {glm::vec3(0.0f, 0.0f, 3.0f)}, cameraFront {glm::vec3(0.0f, 0.0f, -1.0f)}, cameraRight {glm::normalize(glm::cross(cameraFront, cameraUp)) * movementSpeed},
   view {glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp)}, movementSpeed {movementSpeed}, deltaTime {0.0f}, lastFrame {0.0f}, 
   yaw {yaw}, pitch {pitch}, mouseSensitivity {mouseSensitivity}, zoom {zoom}, firstMouseMovement {true}, lastX {}, lastY {}, cameraUp {glm::vec3(0.0f, 1.0f, 0.0f)}  {}


/* Camera class destructor. */
Camera::~Camera()
{

}

void Camera::updateCameraPos()
{
	glm::vec3 direction;
	const double cosPitch {cos(glm::radians(pitch))};

	direction.x = cos(glm::radians(yaw)) * cosPitch;
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cosPitch;	
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
	cameraFront = glm::normalize(direction);
}
