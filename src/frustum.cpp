#include "minecraft/math/frustum.hpp"
#include "minecraft/math/glmath.hpp"


Frustum::Frustum(const glm::vec3 &position, const Camera::CameraDirections &dir, const FrustumView &view) noexcept
{
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
    
}

Frustum Frustum::getCameraFrustum() noexcept
{
    static constexpr float fovTan {1.0f * 0.5f}; // C++ has no constexpr math functions ;(
    static constexpr float adjacent {Camera::far};
    static constexpr float hypotenuse {adjacent * fovTan};
    static constexpr float opposite {hypotenuse * Window::aspectRatio};
    const glm::vec3 farFront {Camera::far * Camera::direction.front};
    const glm::vec3 rightDirection {opposite * Camera::direction.right};
    static constexpr glm::vec3 upDirection {hypotenuse * Camera::up};

    const Plane nearFace {Camera::cameraPos + Camera::near * Camera::direction.front, Camera::direction.front};
    const Plane farFace {Camera::cameraPos + farFront, -Camera::direction.front};
    const Plane rightFace {Camera::cameraPos, glm::cross(Camera::up, farFront + rightDirection)};
    const Plane leftFace {glm::cross(Camera::up, farFront - rightDirection), Camera::cameraPos};
    const Plane topFace {Camera::cameraPos, glm::cross(Camera::direction.right, farFront - upDirection)};
    const Plane bottomFace {Camera::cameraPos, glm::cross(farFront + upDirection, Camera::direction.right)};

    return Frustum{nearFace, farFace, rightFace, leftFace, topFace, bottomFace};
    
}