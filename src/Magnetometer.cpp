#include "Magnetometer.h"

float Magnetometer::getAzimuth(float declination) {
    // Get the magnetic field vector from the device, in uT
    Vector3 magneticField = getMagneticField();

    // Calculate the compass heading
    float heading = atan2(magneticField.y, magneticField.x);

    // Adjust the compass heading for local declination (in rads)
    heading += declination;

    // Adjust for overflow
    if(heading < 0)         heading += 2*M_PI;
    if(heading > 2*M_PI)    heading -= 2*M_PI;

    // Return the heading in degrees
    return heading * 180/M_PI;
}
