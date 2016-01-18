#pragma once

#include "Vector3.h"

/**
 * A thermometer measures temperature in °C.
 */

class Thermometer {
public:
    // Get the current ambient temperature in °C
    virtual float getTemperature() = 0;
};
