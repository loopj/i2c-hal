#pragma once

#include "Vector3.h"

class Barometer {
public:
    // Get the current air pressure in millibars
    virtual double getPressure() = 0;

    // Get the current altitude, in meters
    virtual double getAltitude() = 0;
};
