#include <math.h>

#include "Barometer.h"

const float Barometer::PRESSURE_STANDARD_ATMOSPHERE = 1013.25f;

float Barometer::getAltitude(float baselinePressure) {
    float pressure = getPressure();
    float altitude = 44330 * (1.0 - pow(pressure / baselinePressure, 1 / 5.255));
    return altitude;
}

float Barometer::getSealevelPressure(float altitude) {
    float pressure = getPressure();
    return pressure / pow(1.0 - altitude / 44330, 5.255);
}
