#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "minecraft/physics/ray.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct CameraSettings
{
	float yaw;
	float pitch;
	float speed;
	float sensitivity;
	float zoom;
};

class Camera
{
    public:
		Camera() = default;
    	explicit Camera(const CameraSettings &cameraSettings);
		~Camera() = default;
		CameraSettings settings;
		glm::vec3 cameraPos {0.0f, 0.0f, 3.0f};
		void updateCameraPos();
		inline glm::mat4 getView() const noexcept {return view;}
		inline glm::vec3 getCameraRight() const noexcept {return cameraRight;}
		inline glm::vec3 getCameraFront() const noexcept {return cameraFront;}
		Ray cameraRay {cameraPos, cameraFront, glm::vec3{0.0f, 0.0f, 1.0f}};
	private:
		float deltaTime {0.0f};
		float lastFrame {0.0f};
		glm::mat4 view {glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp)};
		glm::vec3 cameraRight;
		glm::vec3 cameraFront {0.0f, 0.0f, -1.0f};
		glm::vec3 cameraUp {0.0f, 1.0f, 0.0f};
};

#endif // CAMERA_HPP
