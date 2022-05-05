#ifndef FRUSTUM_HPP
#define FRUSTUM_HPP

#include "minecraft/math/plane.hpp"

struct Frustum
{
    Plane topFace;
    Plane bottomFace;
    Plane rightFace;
    Plane leftFace;
    Plane farFace;
    Plane nearFace;
};

#endif // FRUSTUM_HPP
