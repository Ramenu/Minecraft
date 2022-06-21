#include "minecraft/math/frustum.hpp"
#include "minecraft/math/glmath.hpp"
#include "minecraft/window/window.hpp"
#include "misc/boilerplate/gcem_noerr.hpp"
#include "GLFW/glfw3.h"

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
    Frustum frustum;
    #if 1
    static constexpr float HEIGHT_FAR_HALF {gcem::tan(Camera::FOV.value() / 2.0f) * Camera::FAR};
    static constexpr float WIDTH_FAR_HALF {HEIGHT_FAR_HALF * Window::ASPECT_RATIO};
    const glm::vec3 frontMultFar {Camera::direction.front * Camera::FAR};
    const glm::vec3 rightNormal {glm::normalize(frontMultFar + Camera::direction.right * WIDTH_FAR_HALF)};
    const glm::vec3 leftNormal {glm::normalize(frontMultFar - Camera::direction.right * WIDTH_FAR_HALF)};
    const glm::vec3 upNormal {glm::normalize(frontMultFar - Camera::CAMERA_UP * HEIGHT_FAR_HALF)};
    const glm::vec3 downNormal {glm::normalize(frontMultFar + Camera::CAMERA_UP * HEIGHT_FAR_HALF)};

    frustum.nearFace = {Camera::cameraPos + Camera::FAR * Camera::direction.front, Camera::direction.front};
    frustum.farFace = {Camera::cameraPos + frontMultFar, -Camera::direction.front};
    frustum.rightFace = {Camera::cameraPos, glm::normalize(glm::cross(Camera::CAMERA_UP, rightNormal))};
    frustum.leftFace = {Camera::cameraPos, glm::normalize(glm::cross(leftNormal, Camera::CAMERA_UP))};
    frustum.topFace = {Camera::cameraPos, glm::normalize(glm::cross(Camera::direction.right, upNormal))};
    frustum.bottomFace = {Camera::cameraPos, glm::normalize(glm::cross(downNormal, Camera::direction.right))};

    /*if (glfwGetKey(Window::getWindow(), GLFW_KEY_Z) == GLFW_PRESS)
    {
        printf("----------\n"
               "Near face: %f\n"
               "Far face: %f\n"
               "Right face: %f\n"
               "Left face: %f\n", static_cast<double>(frustum.farFace.distance),
                                   static_cast<double>(frustum.nearFace.distance),
                                   static_cast<double>(frustum.rightFace.distance),
                                   static_cast<double>(frustum.leftFace.distance));
    }*/
    #endif

    return frustum;

}

/*
bool Frustum::isInFrustum(const glm::vec3 &position, const glm::vec3 &offset) const noexcept
{
    const glm::vec3 posOffset {position + offset};
    #if 1
    const float distToNear {nearFace.getSignedDistanceToPlane(position)};
    const float distToFar {farFace.getSignedDistanceToPlane(posOffset)};
    
    const float distToBottom {bottomFace.getSignedDistanceToPlane(position)};
    const float distToTop {topFace.getSignedDistanceToPlane(position)};
    if (glfwGetKey(Window::getWindow(), GLFW_KEY_Z) == GLFW_PRESS)
    {
        printf("----------\n"
               "Distance to top: %f\n"
               "Distance to bottom: %f\n", static_cast<double>(distToTop),
                                        static_cast<double>(distToBottom));
        printf("Bottom face distance: %f\n", static_cast<double>(distToTop));
    }

    return (nearFace.distance >= distToNear && farFace.distance <= distToFar) &&
           (bottomFace.distance >= distToBottom && topFace.distance <= distToTop);
    #else
    const float distToBottom {glm::dot(position, bottomFace.normal)};
    const float distToUp {glm::dot(glm::normalize(position + offset), topFace.normal)};

    if (glfwGetKey(Window::getWindow(), GLFW_KEY_Z) == GLFW_PRESS)
    {
        printf("----------\n"
               "Distance to top: %f\n", static_cast<double>(topFace.distance - distToUp));
    }

    return (bottomFace.distance >= distToBottom && topFace.distance <= distToUp);
    #endif
}*/