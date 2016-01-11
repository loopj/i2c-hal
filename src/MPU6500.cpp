#include "config.h"

#ifdef MPU6500_INSTALLED

#include "Accelerometer.h"
#include "MPU6500.h"
#include "application.h"

MPU6500::MPU6500(uint8_t address) {
    this->address = address;
}

void MPU6500::initialize() {
    setSleepEnabled(false);

    accelScale = 2048.0 * pow(2, 3 - getFullScaleAccelRange());
    gyroScale = 16.4 * pow(2, 3 - getFullScaleGyroRange());
}

void MPU6500::setSleepEnabled(bool enabled) {
    writeBit(RA_PWR_MGMT_1, MPU6500_PWR1_SLEEP_BIT, enabled);
}

Vector3 MPU6500::getAcceleration() {
    int16_t buf[3];
    readWords(RA_ACCEL_XOUT_H, 3, (uint16_t *)buf);

    return Vector3((double)buf[0]/accelScale * STANDARD_GRAVITY, (double)buf[1]/accelScale * STANDARD_GRAVITY, (double)buf[2]/accelScale * STANDARD_GRAVITY);
}

Vector3 MPU6500::getRotation() {
    int16_t buf[3];
    readWords(RA_GYRO_XOUT_H, 3, (uint16_t *)buf);

    return Vector3((double)buf[0]/gyroScale * M_PI/180.0, (double)buf[1]/gyroScale * M_PI/180.0, (double)buf[2]/gyroScale * M_PI/180.0);
}

uint8_t MPU6500::getFullScaleGyroRange() {
    readBits(RA_GYRO_CONFIG, MPU6500_GCONFIG_FS_SEL_BIT, MPU6500_GCONFIG_FS_SEL_LENGTH, buffer);

    return buffer[0];
}

uint8_t MPU6500::getFullScaleAccelRange() {
    readBits(RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, buffer);

    return buffer[0];
}

#endif // MPU6500_INSTALLED
