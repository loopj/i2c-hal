#include "config.h"

#ifdef MPU6050_INSTALLED

#include "HAL_MPU6050.h"

void HAL_MPU6050::initialize() {
    device.initialize();

    // Allow direct access to other sensors on the i2c bus
    device.setI2CBypassEnabled(true);

    accelScale = 2048.0 * pow(2, 3 - device.getFullScaleAccelRange());
    gyroScale = 16.4 * pow(2, 3 - device.getFullScaleGyroRange());
}

Vector3 HAL_MPU6050::getAcceleration() {
    // Get the raw accelerometer readings
    int16_t rax, ray, raz;
    device.getAcceleration(&rax, &ray, &raz);

    // Convert raw accelerometer readings into m/s^2
    return Vector3(ACCELEROMETER_ORIENTATION(((double)rax/accelScale) * STANDARD_GRAVITY, ((double)ray/accelScale) * STANDARD_GRAVITY, ((double)raz/accelScale) * STANDARD_GRAVITY));
}

Vector3 HAL_MPU6050::getRotation() {
    // Get the raw gyroscope readings
    int16_t rgx, rgy, rgz;
    device.getRotation(&rgx, &rgy, &rgz);

    // Convert raw gyroscope readings into rad/s
    return Vector3(GYROSCOPE_ORIENTATION(((double)rgx/gyroScale) * M_PI/180.0, ((double)rgy/gyroScale) * M_PI/180.0, ((double)rgz/gyroScale) * M_PI/180.0));
}

double HAL_MPU6050::getTemperature() {
    int16_t rt = device.getTemperature();

    // Convert raw temperature reading to C
    return (double)rt/340.0 + 36.53;
}

#endif // MPU6050_INSTALLED
