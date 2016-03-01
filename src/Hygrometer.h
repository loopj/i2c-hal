#pragma once

#include "Vector3.h"

/**
 * A hygrometer measures the moisture content in the atmosphere, or
 * relative humidity, as a percentage.
 */

class Hygrometer {
public:
    // Get the current relative humidity, as a percentage
    virtual float getRelativeHumidity() = 0;
};
