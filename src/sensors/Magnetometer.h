#pragma once

#include "Vector3.h"

/**
 * A magnetometer measures the strength and direction of magnetic fields
 * in μT, on three axes.
 *
 * Using magnetic field readings from a magnetometer, you can also compute
 * the azimuth (or compass direction) of your device.
 */

class Magnetometer {
public:
    // Gauss to microTesla multiplier
    static const float GAUSS_TO_MICROTESLA;

    // Get the current magnetic field vector, in μT
    virtual Vector3 getMagneticField() = 0;

    // Get the current azimuth (compass direction), optionally adjusting for declination
    float getAzimuth(float declination = 0.0);
};
