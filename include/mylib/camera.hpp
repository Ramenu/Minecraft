#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "mylib/physics/ray.hpp"

class Camera
{
    public:
        Camera(const float yaw, const float pitch, const float movementSpeed, const float mouseSensitivty, const float zoom);
		~Camera();
		glm::vec3 cameraPos;
		glm::vec3 cameraFront;
		glm::vec3 cameraRight;
		glm::mat4 view;
		void updateCameraPos();
		float movementSpeed;
		double deltaTime;
		double lastFrame;
		float yaw;
		float pitch;
		float mouseSensitivity;
		float zoom;
		bool firstMouseMovement;
		double lastX;
		double lastY;
	private:
		glm::vec3 cameraUp;
		Ray cameraRay;
};

#endif // CAMERA_HPP
