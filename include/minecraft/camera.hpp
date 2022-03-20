#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "minecraft/physics/ray.hpp"
#include "glm/gtc/matrix_transform.hpp"


struct CameraSettings
{
	float yaw;
	float pitch;
	float sensitivity;
};

class Camera
{
    public:
		Camera() = default;
    	Camera(const CameraSettings &cameraSettings) noexcept;
		~Camera() = default;
		CameraSettings settings;
		glm::vec3 cameraPos {0.0f, 0.0f, 3.0f};
		void updateCameraPos(double cursorX, double cursorY) noexcept;
		inline glm::mat4 getView() const noexcept {return view;}
		inline glm::vec3 getCameraFront() const noexcept {return cameraFront;}
		inline glm::vec3 getCameraRight() const noexcept {return cameraRight;}
	private:
		glm::vec3 cameraFront {0.0f, 0.0f, -1.0f};
		glm::vec3 cameraUp {0.0f, 1.0f, 0.0f};
		glm::vec3 cameraRight;
		glm::mat4 view;
	public:
		Ray ray {cameraPos, cameraFront};
	
};

#endif // CAMERA_HPP
