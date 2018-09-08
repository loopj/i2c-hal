#pragma once

#include "Vector3.h"

/**
 * A barometer measures atmospheric pressure in hPa or mbar.
 *
 * Using atmospheric pressure from a barometer, you can also compute the
 * altitude in meters.
 */

class Barometer {
public:
    // Standard atmosphere, or average sea-level pressure in hPa (millibars)
    static const float PRESSURE_STANDARD_ATMOSPHERE;

    // Get the current air pressure in hPa
    virtual float getPressure() = 0;

    // Get the current altitude in m, given a baseline pressure in hPa
    float getAltitude(float baselinePressure = PRESSURE_STANDARD_ATMOSPHERE);

    // Get the pressure at sea-level in hPa, given the current altitude in m
    float getSealevelPressure(float altitude);
};
