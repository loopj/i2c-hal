#include "config.h"

#ifdef HMC5883L_INSTALLED

#include <stdint.h>
#include "HAL_HMC5883L.h"

void HAL_HMC5883L::initialize() {
    device.initialize();
    device.setDataRate(HMC5883L_RATE_75);
    device.setGain(HMC5883L_GAIN_1090);

    magScale = 1090.0;
}

Vector3 HAL_HMC5883L::getHeading() {
    Vector3 heading;

    // Get the raw compass readings
    int16_t rhx, rhy, rhz;
    device.getHeading(&rhx, &rhy, &rhz);

    // Convert raw compass readings into Gauss
    heading.x = (double)rhx/magScale;
    heading.y = (double)rhy/magScale;
    heading.z = (double)rhz/magScale;

    return heading;
}

#endif // HMC5883L_INSTALLED
