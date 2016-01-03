#include "config.h"

#ifdef AK8963_INSTALLED

#include "HAL_AK8963.h"

// TODO: Get this working and outputting milliGauss

void HAL_AK8963::initialize() {
    device.setMode(AK8963_MODE_POWERDOWN);
    delay(10);
    device.setMode(AK8963_MODE_FUSEROM);
    delay(10);

    int8_t ax, ay, az;
    device.getAdjustment(&ax, &ay, &az);

    Serial.println(ax);
    Serial.println(ay);
    Serial.println(az);
    Serial.println();

    device.setMode(AK8963_MODE_CONTINUOUS_8HZ);
    device.setResolution(AK8963_RES_16_BIT);
    delay(10);

    // Calculate the scale factor
    uint8_t res = device.getResolution();
    if(res = AK8963_RES_14_BIT) {
        // Conversion to milliGauss when in 14-bit mode
        scale = 10.0 * 4912.0 / 8190.0;
    } else {
        // Conversion to milliGauss when in 16-bit mode
        scale = 10.0 * 4912.0 / 32760.0;
    }
}

Vector3 HAL_AK8963::getHeading() {
    // Get the raw compass readings
    int16_t rhx, rhy, rhz;
    device.getHeading(&rhx, &rhy, &rhz);

    // Convert raw compass readings into milliGauss
    return Vector3(COMPASS_ORIENTATION((double)rhx*scale, (double)rhy*scale, (double)rhz*scale));
}

#endif // AK8963_INSTALLED
