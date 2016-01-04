#include "config.h"

#ifdef AK8963_INSTALLED

#include "HAL_AK8963.h"

// TODO: Get this working and outputting milliGauss

void HAL_AK8963::initialize() {
    // Enter "fuse rom" mode to fetch sensitivity adjustment
    device.setMode(AK8963_MODE_FUSEROM);
    delay(10);

    // Get raw sensitivity adjustment values from Fuse rom
    int8_t asax, asay, asaz;
    device.getAdjustment(&asax, &asay, &asaz);

    // Sensitivity adjustment (from AK8963 datasheet 8.3.11)
    adjustment.x = ((double)asax - 128)/256.0 + 1.0;
    adjustment.y = ((double)asay - 128)/256.0 + 1.0;
    adjustment.z = ((double)asaz - 128)/256.0 + 1.0;

    Serial.println(adjustment.x);
    Serial.println(adjustment.y);
    Serial.println(adjustment.z);
    Serial.println();

    // Switch to continuous mode
    device.setMode(AK8963_MODE_POWERDOWN);
    delay(10);
    device.setMode(AK8963_MODE_CONTINUOUS_8HZ);
    device.setResolution(AK8963_RES_16_BIT);
    delay(10);

    // Calculate the scale factor based on the configured resolution
    uint8_t res = device.getResolution();
    if(res == AK8963_RES_14_BIT) {
        // Conversion to milliGauss when in 14-bit mode (0.6 mG per LSB)
        scale = 4912.0 / 8190.0;
    } else {
        // Conversion to milliGauss when in 16-bit mode (0.15 mG per LSB)
        scale = 4912.0 / 32760.0;
    }
}

Vector3 HAL_AK8963::getHeading() {
    int16_t rhx, rhy, rhz;
    device.getHeading(&rhx, &rhy, &rhz);
    device.getOverflowStatus();

    // Convert raw compass readings into milliGauss
    return Vector3(COMPASS_ORIENTATION((double)rhx*adjustment.x*scale, (double)rhy*adjustment.y*scale, (double)rhz*adjustment.z*scale));
}

#endif // AK8963_INSTALLED
