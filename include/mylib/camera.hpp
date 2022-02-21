#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "mylib/physics/ray.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
    public:
    	Camera(float yaw, float pitch, float speed, float sensitivity, float zoom);
		~Camera();
		glm::vec3 cameraPos {glm::vec3(0.0f, 0.0f, 3.0f)};
		glm::vec3 cameraFront {glm::vec3(0.0f, 0.0f, -1.0f)};
		glm::vec3 cameraRight {glm::normalize(glm::cross(cameraFront, cameraUp)) * movementSpeed};
		glm::mat4 view {glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp)};
		void updateCameraPos();
		float yaw;
		float pitch;
		float movementSpeed;
		float mouseSensitivity;
		float zoom;
		float deltaTime {0.0f};
		float lastFrame {0.0f};
	private:
		bool firstMouseMovement {true};
		double lastX;
		double lastY;
		glm::vec3 cameraUp {glm::vec3(0.0f, 1.0f, 0.0f)};
		Ray cameraRay {cameraPos, cameraFront, glm::vec3(0.0f, 0.0f, 2.0f)};
};

#endif // CAMERA_HPP
