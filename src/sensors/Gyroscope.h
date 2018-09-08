#pragma once

#include "Vector3.h"

/**
 * A gyroscope measures the rotational speed in rad/s, on three axes.
 */

class Gyroscope {
public:
    // Get the current rotational speed vector, in rad/s
    virtual Vector3 getRotation() = 0;
};
