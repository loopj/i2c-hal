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
    // Get the current heading vector, in milliGauss
    virtual Vector3 getMagneticField() = 0;
};
