#ifndef MC_FRUSTUM_HPP
#define MC_FRUSTUM_HPP

#include "minecraft/math/plane.hpp"
#include "minecraft/camera/camera.hpp"

struct FrustumView
{
    float aspectRatio;
    Radians fov;
    float zNear;
    float zFar;
};

class Frustum
{
    private:
        Plane nearFace;
        Plane farFace;
        Plane rightFace;
        Plane leftFace;
        Plane topFace;
        Plane bottomFace;
    public:
        Frustum(const Plane &near, const Plane &far, const Plane &right,
                const Plane &left, const Plane &top, const Plane &bottom) noexcept :
                nearFace {near}, farFace {far}, rightFace {right},
                leftFace {left}, topFace {top}, bottomFace {bottom} {}

        Frustum(const glm::vec3 &position, const Camera::CameraDirections &directions, const FrustumView &view) noexcept;
        [[nodiscard]] static Frustum getCameraFrustum() noexcept;
        inline Plane getNearFace() const noexcept {return nearFace;}
        inline Plane getFarFace() const noexcept {return farFace;}
        inline Plane getRightFace() const noexcept {return rightFace;}
        inline Plane getLeftFace() const noexcept {return leftFace;}
        inline Plane getTopFace() const noexcept {return topFace;}
        inline Plane getBottomFace() const noexcept {return bottomFace;}
};

#endif // MC_FRUSTUM_HPP
