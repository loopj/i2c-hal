#pragma once

#include "Vector3.h"

class Gyroscope {
public:
    // Get the current rotational speed vector, in degrees per second
    virtual Vector3 getRotation() = 0;
};
