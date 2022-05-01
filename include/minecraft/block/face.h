#ifndef FACE_H
#define FACE_H

#include <stdint.h>

enum Face : uint8_t
{
    BackFace = 0,
    FrontFace = 1,
    RightFace = 2,
    LeftFace = 3,
    TopFace = 4,
    BottomFace = 5
};

#endif // FACE_H
