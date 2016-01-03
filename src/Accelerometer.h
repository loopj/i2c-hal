#pragma once

#include "Vector3.h"

class Accelerometer {
public:
    // Get the current acceleration vector, in Gs
    virtual Vector3 getAcceleration() = 0;
};
