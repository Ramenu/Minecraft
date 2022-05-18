#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "minecraft/rendering/chunk.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "minecraft/math/radians.hpp"
#include "minecraft/ray.hpp"


namespace Camera
{
	static constexpr float near {0.1f}, far {100.0f};
	static constexpr float speed {12.0f};
	static constexpr Radians fov {45.0f};
	static constexpr glm::vec3 up {0.0f, 1.0f, 0.0f};

	struct CameraSettings
	{
		float yaw;
		float pitch;
		float sensitivity;
	};

	struct CameraDirections
	{
		glm::vec3 front {0.0f, 0.0f, -1.0f};
		glm::vec3 right {glm::normalize(glm::cross(front, Camera::up)) * Camera::speed};
	};

	inline Ray ray;
	extern void initCameraRay(const glm::vec3 &origin, const glm::vec3 &dir, const glm::vec3 &length);
	extern Ray getRay() noexcept;
	extern glm::mat4 getView() noexcept;
	extern void updateCameraPos() noexcept;
	inline CameraSettings settings {.yaw = 90.0f, .pitch = 0.0f, .sensitivity = 0.1f};
	inline CameraDirections direction;
	inline glm::vec3 cameraPos {0.0f, chunkHeight * 2, 3.0f};

}

#endif // CAMERA_HPP
