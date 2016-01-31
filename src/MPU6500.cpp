#include "Sensor_Config.h"

#ifdef MPU6500_INSTALLED

#include "MPU6500.h"

// Initialization
MPU6500::MPU6500(uint8_t address) {
    this->address = address;
}

void MPU6500::initialize() {
    // Wake up the device
    setSleepEnabled(false);

    // Use the most accurate clock source
    setClockSource(MPU6500_CLOCK_PLL);

    // Set the sensitivity to max on gyro and accel
    setFullScaleGyroRange(MPU6500_GYRO_FS_250);
    setFullScaleAccelRange(MPU6500_ACCEL_FS_2);

    // Allow direct I2C access to devices connected to the MPU6500 aux bus
    setI2cBypassEnabled(true);

    // Calculate the scale factors from the configured ranges
    accelScale = getAccelScale(getFullScaleAccelRange());
    gyroScale = getGyroScale(getFullScaleGyroRange());
}

bool MPU6500::testConnection() {
    return getDeviceID() == MPU6500_DEVICE_ID;
}

// Accelerometer
Vector3 MPU6500::getAcceleration() {
    Vector3 acceleration;

    // Read raw acceleration data from device
    int16_t rawAccel[3];
    readWords(MPU6500_RA_ACCEL_XOUT_H, 3, (uint16_t *)rawAccel);

    // Apply accelerometer scale to get Gs, convert to m/s^2
    acceleration.x = (float)rawAccel[0]/accelScale * STANDARD_GRAVITY;
    acceleration.y = (float)rawAccel[1]/accelScale * STANDARD_GRAVITY;
    acceleration.z = (float)rawAccel[2]/accelScale * STANDARD_GRAVITY;

    return acceleration;
}

// Gyroscope
Vector3 MPU6500::getRotation() {
    Vector3 rotation;

    // Read raw rotation data from device
    int16_t rawRotation[3];
    readWords(MPU6500_RA_GYRO_XOUT_H, 3, (uint16_t *)rawRotation);

    // Apply gyroscope scale to get deg/s, convert to rad/s
    rotation.x = (float)rawRotation[0]/gyroScale * M_PI/180.0;
    rotation.y = (float)rawRotation[1]/gyroScale * M_PI/180.0;
    rotation.z = (float)rawRotation[2]/gyroScale * M_PI/180.0;

    return rotation;
}

// GYRO_CONFIG register
uint8_t MPU6500::getFullScaleGyroRange() {
    readBits(MPU6500_RA_GYRO_CONFIG, MPU6500_GYRO_FS_SEL_BIT, MPU6500_GYRO_FS_SEL_LEN, buffer);

    return buffer[0];
}

void MPU6500::setFullScaleGyroRange(uint8_t range) {
    writeBits(MPU6500_RA_GYRO_CONFIG, MPU6500_GYRO_FS_SEL_BIT, MPU6500_GYRO_FS_SEL_LEN, range);
    gyroScale = getGyroScale(range);
}

// ACCEL_CONFIG register
uint8_t MPU6500::getFullScaleAccelRange() {
    readBits(MPU6500_RA_ACCEL_CONFIG, MPU6500_ACCEL_FS_SEL_BIT, MPU6500_ACCEL_FS_SEL_LEN, buffer);

    return buffer[0];
}

void MPU6500::setFullScaleAccelRange(uint8_t range) {
    writeBits(MPU6500_RA_ACCEL_CONFIG, MPU6500_ACCEL_FS_SEL_BIT, MPU6500_ACCEL_FS_SEL_LEN, range);
    accelScale = getAccelScale(range);
}

// INT_PIN_CFG register
bool MPU6500::getI2cBypassEnabled() {
    readBit(MPU6500_RA_INT_PIN_CFG, MPU6500_BYPASS_EN_BIT, buffer);
    return buffer[0];
}

void MPU6500::setI2cBypassEnabled(bool enabled) {
    writeBit(MPU6500_RA_INT_PIN_CFG, MPU6500_BYPASS_EN_BIT, enabled);
}

// USER_CTRL register
bool MPU6500::getDMPEnabled() {
    readBit(MPU6500_RA_USER_CTRL, MPU6500_DMP_EN_BIT, buffer);
    return buffer[0];
}

void MPU6500::setDMPEnabled(bool enabled) {
    writeBit(MPU6500_RA_USER_CTRL, MPU6500_DMP_EN_BIT, enabled);
}

// PWR_MGMT_1 register
void MPU6500::reset() {
    writeBit(MPU6500_RA_PWR_MGMT_1, MPU6500_DEVICE_RESET_BIT, 1);
}

bool MPU6500::getSleepEnabled() {
    readBit(MPU6500_RA_PWR_MGMT_1, MPU6500_SLEEP_BIT, buffer);
    return buffer[0];
}

void MPU6500::setSleepEnabled(bool enabled) {
    writeBit(MPU6500_RA_PWR_MGMT_1, MPU6500_SLEEP_BIT, enabled);
}

uint8_t MPU6500::getClockSource() {
    readBits(MPU6500_RA_PWR_MGMT_1, MPU6500_CLKSEL_BIT, MPU6500_CLKSEL_LEN, buffer);
    return buffer[0];
}

void MPU6500::setClockSource(uint8_t source) {
    writeBits(MPU6500_RA_PWR_MGMT_1, MPU6500_CLKSEL_BIT, MPU6500_CLKSEL_LEN, source);
}

// WHO_AM_I register
uint8_t MPU6500::getDeviceID() {
    readByte(MPU6500_RA_WHO_AM_I, buffer);
    return buffer[0];
}

// Private
float MPU6500::getGyroScale(uint8_t gyroRange) {
    return 16.4 * pow(2, 3 - gyroRange);
}

float MPU6500::getAccelScale(uint8_t accelRange) {
    return 2048.0 * pow(2, 3 - accelRange);
}

#endif // MPU6500_INSTALLED
