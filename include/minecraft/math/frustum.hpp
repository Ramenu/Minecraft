#ifndef MC_FRUSTUM_HPP
#define MC_FRUSTUM_HPP

#include "minecraft/math/plane.hpp"
#include "minecraft/camera/camera.hpp"
#include "minecraft/math/shape/sphere.hpp"

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
        Plane nearFace{};
        Plane farFace{};
        Plane rightFace{};
        Plane leftFace{};
        Plane topFace{};
        Plane bottomFace{};
    public:
        Frustum() = default;
        Frustum(const Plane &near, const Plane &far, const Plane &right,
                const Plane &left, const Plane &top, const Plane &bottom) noexcept :
                nearFace {near}, farFace {far}, rightFace {right},
                leftFace {left}, topFace {top}, bottomFace {bottom} {}

        Frustum(const glm::vec3 &position, const Camera::CameraDirections &directions, const FrustumView &view) noexcept;
        [[nodiscard]] static Frustum getCameraFrustum() noexcept;
        inline bool isInFrustum(const Sphere &boundingSphere) const noexcept {
            return (
                boundingSphere.isOnForwardPlane(nearFace) &&
                boundingSphere.isOnForwardPlane(farFace) &&
                boundingSphere.isOnForwardPlane(rightFace) &&
                boundingSphere.isOnForwardPlane(leftFace) &&
                boundingSphere.isOnForwardPlane(topFace) &&
                boundingSphere.isOnForwardPlane(bottomFace)
            );
        }
};

#endif // MC_FRUSTUM_HPP
