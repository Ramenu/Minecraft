#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "minecraft/rendering/chunk.hpp"
#include "minecraft/physics/ray.hpp"
#include "glm/gtc/matrix_transform.hpp"

static constexpr float speed {6.0f};
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
	glm::vec3 right {glm::normalize(glm::cross(front, up)) * speed};
};

namespace Camera
{
	extern glm::mat4 getView() noexcept;
	extern void updateCameraPos(double cursorX, double cursorY) noexcept;
	inline CameraSettings settings {.yaw = 90.0f, .pitch = 0.0f, .sensitivity = 0.1f};
	inline CameraDirections direction;
	inline glm::vec3 cameraPos {0.0f, chunkHeight * 2, 3.0f};
	inline Ray ray {cameraPos, direction.front};

}

#endif // CAMERA_HPP
