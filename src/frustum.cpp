#include "minecraft/math/frustum.hpp"
#include "minecraft/math/glmath.hpp"
#include "minecraft/window/window.hpp"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#include "gcem/gcem.hpp"
#pragma GCC diagnostic pop


Frustum::Frustum([[maybe_unused]] const glm::vec3 &position, [[maybe_unused]] const Camera::CameraDirections &dir, [[maybe_unused]] const FrustumView &view) noexcept
{
    #if 0
    static constexpr glm::vec3 up {0.0f, 1.0f, 0.0f};
    const float adjacent {view.zFar};
    const float hypotenuse {adjacent * std::tan(view.fov.value() * 0.5f)};
    const float opposite {hypotenuse * view.aspectRatio};
    const glm::vec3 farFront {view.zFar * dir.front};
    const glm::vec3 rightDirection {opposite * dir.right};
    const glm::vec3 upDirection {hypotenuse * up};

    nearFace = {position + view.zNear * dir.front, dir.front};
    farFace = {position + farFront, -dir.front};
    rightFace = {position, glm::cross(up, farFront + rightDirection)};
    leftFace = {glm::cross(up, farFront - rightDirection), position};
    topFace = {position, glm::cross(dir.right, farFront - upDirection)};
    bottomFace = {position, glm::cross(farFront + upDirection, dir.right)};
    #endif
    
}

Frustum Frustum::getCameraFrustum() noexcept
{
    return Frustum{Plane{}, Plane{}, Plane{}, Plane{}, Plane{}, Plane{}};
}