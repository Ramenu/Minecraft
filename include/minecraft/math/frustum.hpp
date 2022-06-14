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
        Plane negZ;
        Plane posZ;
        Plane posX;
        Plane negX;
        Plane posY;
        Plane negY;
    public:
        // Near -> negZ
        // Far -> posZ
        Frustum(const Plane &near, const Plane &far, const Plane &right,
                const Plane &left, const Plane &top, const Plane &bottom) noexcept :
                negZ {near}, posZ {far}, posX {right},
                negX {left}, posY {top}, negY {bottom} {}

        Frustum(const glm::vec3 &position, const Camera::CameraDirections &directions, const FrustumView &view) noexcept;
        [[nodiscard]] static Frustum getCameraFrustum() noexcept;
};

#endif // MC_FRUSTUM_HPP
