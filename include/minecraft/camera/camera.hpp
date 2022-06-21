#ifndef MC_CAMERA_HPP
#define MC_CAMERA_HPP

#include "minecraft/rendering/chunk.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "minecraft/math/radians.hpp"
#include "minecraft/ray.hpp"


namespace Camera
{
	static constexpr float NEAR {0.1f}, FAR {100.0f};
	static constexpr float SPEED {12.0f};
	static constexpr Radians FOV {45.0f};
	static constexpr glm::vec3 CAMERA_UP {0.0f, 1.0f, 0.0f};

	struct CameraSettings
	{
		float yaw;
		float pitch;
		float sensitivity;
	};

	struct CameraDirections
	{
		glm::vec3 front {0.0f, 0.0f, -1.0f};
		glm::vec3 right {glm::normalize(glm::cross(front, CAMERA_UP)) * SPEED};
	};

	extern glm::i32vec3 getCameraPosChunkOffset() noexcept;
	extern Ray getCameraRay() noexcept;
	extern glm::mat4 getView() noexcept;
	extern void updateCameraPos() noexcept;
	inline CameraSettings settings {.yaw = 90.0f, .pitch = 0.0f, .sensitivity = 0.1f};
	inline CameraDirections direction;
	inline glm::vec3 cameraPos {0.0f, CHUNK_HEIGHT * 2, 3.0f};

}

#endif // MC_CAMERA_HPP
