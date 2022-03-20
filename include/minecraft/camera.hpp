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

struct CameraDirections
{
	glm::vec3 front {0.0f, 0.0f, -1.0f};
	glm::vec3 up {0.0f, 1.0f, 0.0f};
	glm::vec3 right {glm::normalize(glm::cross(front, up)) * speed};
};

class Camera
{
    public:
		Camera() = default;
    	inline Camera(const CameraSettings &cameraSettings) noexcept : settings {cameraSettings} {}
		~Camera() = default;
		CameraSettings settings;
		glm::vec3 cameraPos {0.0f, 0.0f, 3.0f};
		void updateCameraPos(double cursorX, double cursorY) noexcept;
		inline glm::mat4 getView() const noexcept {return view;}
		CameraDirections direction;
	private:
		glm::mat4 view;
	public:
		Ray ray {cameraPos, direction.front};
	
};

#endif // CAMERA_HPP
