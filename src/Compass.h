#pragma once

#include "Vector3.h"

class Compass {
public:
    // Run any sensor initialization
    virtual void initialize() = 0;

    // Get the current heading vector, in milliGauss
    virtual Vector3 getHeading() = 0;
};
