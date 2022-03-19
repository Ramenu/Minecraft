#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "minecraft/physics/ray.hpp"
#include "glm/gtc/matrix_transform.hpp"

constexpr float speed {2.5f};

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
    	Camera(const CameraSettings &cameraSettings, const glm::vec3 &cameraPos);
		~Camera() = default;
		CameraSettings settings;
		void updateCameraPos(double cursorX, double cursorY, const glm::vec3 &cameraPos);
		inline glm::mat4 getView() const noexcept {return view;}
		inline glm::vec3 getCameraFront() const noexcept {return cameraFront;}
		inline glm::vec3 getCameraRight() const noexcept {return cameraRight;}
	private:
		glm::vec3 cameraFront {0.0f, 0.0f, -1.0f};
		glm::vec3 cameraUp {0.0f, 1.0f, 0.0f};
		glm::vec3 cameraRight;
		glm::mat4 view;
		Line rayLine;
	public:
		Ray ray {rayLine};
	
};

#endif // CAMERA_HPP
