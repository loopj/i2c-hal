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
    static constexpr float PRESSURE_STANDARD_ATMOSPHERE = 1013.25F;

    // Get the current air pressure in hPa (millibars)
    virtual float getPressure() = 0;
};
