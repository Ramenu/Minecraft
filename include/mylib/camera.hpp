#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

class Camera
{
    public:
        Camera(const float& yaw, const float& pitch, const float& movementSpeed, const float& mouseSensitivty, const float& zoom);
		~Camera();
		glm::vec3 cameraPos;
		glm::vec3 cameraFront;
		glm::vec3 cameraRight;
		glm::mat4 view;
		void updateCameraPos(GLFWwindow* window);
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
};



#endif
