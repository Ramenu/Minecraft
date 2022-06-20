#include "minecraft/math/frustum.hpp"
#include "minecraft/math/glmath.hpp"
#include "minecraft/window/window.hpp"
#include "misc/boilerplate/gcem_noerr.hpp"

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
    /*static constexpr float HEIGHT_NEAR {2.0f * gcem::tan(Camera::FOV.value() / 2.0f) * Camera::NEAR};
    static constexpr float WIDTH_NEAR {HEIGHT_NEAR * Window::ASPECT_RATIO};

    static constexpr float HEIGHT_FAR {2.0f * gcem::tan(Camera::FOV.value() / 2.0f) * Camera::FAR};
    static constexpr float WIDTH_FAR {HEIGHT_FAR * Window::ASPECT_RATIO};*/
    return Frustum{Plane{}, Plane{}, Plane{}, Plane{}, Plane{}, Plane{}};
}