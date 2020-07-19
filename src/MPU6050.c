#pragma once

#include "MPU6050.h"

float accelScale;
float gyroScale;
uint8_t address;
uint8_t buffer[6];

float MPU6050_getGyroScale(uint8_t gyroRange);
float MPU6050_getAccelScale(uint8_t accelRange);

// Initialization
void MPU6050_initialize(uint8_t deviceAddress) {
    address = deviceAddress;

    // Wake up the device
    MPU6050_setSleepEnabled(false);

    // Use the most accurate clock source
    MPU6050_setClockSource(MPU6050_CLOCK_PLL);

    // Set the sensitivity to max on gyro and accel
    MPU6050_setFullScaleGyroRange(MPU6050_GYRO_FS_250);
    MPU6050_setFullScaleAccelRange(MPU6050_ACCEL_FS_2);

    // Allow direct I2C access to devices connected to the MPU6050 aux bus
    MPU6050_setI2cBypassEnabled(true);

    // Calculate the scale factors from the configured ranges
    accelScale = MPU6050_getAccelScale(getFullScaleAccelRange());
    gyroScale = MPU6050_getGyroScale(getFullScaleGyroRange());
}

bool MPU6050_testConnection() {
    switch(MPU6050_getDeviceID()) {
        case MPU6050_DEVICE_ID:
            return true;
        case MPU6500_DEVICE_ID:
            return true;
        case MPU9150_DEVICE_ID:
            return true;
        case MPU9250_DEVICE_ID:
            return true;
    }

    return false;
}

// Accelerometer
Vector3 MPU6050_getAcceleration() {
    Vector3 acceleration;

    // Convert raw data into signed 16-bit data
    int16_t rawAccel[3];
    I2C_readWords(address, MPU6050_RA_ACCEL_XOUT_H, 3, (uint16_t *)rawAccel);

    // Apply accelerometer scale to get Gs, convert to m/s^2
    acceleration.x = (float)rawAccel[0]/accelScale * STANDARD_GRAVITY;
    acceleration.y = (float)rawAccel[1]/accelScale * STANDARD_GRAVITY;
    acceleration.z = (float)rawAccel[2]/accelScale * STANDARD_GRAVITY;

    return acceleration;
}

// Gyroscope
Vector3 MPU6050_getRotation() {
    Vector3 rotation;

    // Convert raw data into signed 16-bit data
    int16_t rawRotation[3];
    I2C_readWords(address, MPU6050_RA_GYRO_XOUT_H, 3, (uint16_t *)rawRotation);

    // Apply gyroscope scale to get deg/s, convert to rad/s
    rotation.x = (float)rawRotation[0]/gyroScale * M_PI/180.0;
    rotation.y = (float)rawRotation[1]/gyroScale * M_PI/180.0;
    rotation.z = (float)rawRotation[2]/gyroScale * M_PI/180.0;

    return rotation;
}

// GYRO_CONFIG register
uint8_t MPU6050_getFullScaleGyroRange() {
    I2C_readBits(address, MPU6050_RA_GYRO_CONFIG, MPU6050_GYRO_FS_SEL_BIT, MPU6050_GYRO_FS_SEL_LEN, buffer);

    return buffer[0];
}

void MPU6050_etFullScaleGyroRange(uint8_t range) {
    I2C_writeBits(address, MPU6050_RA_GYRO_CONFIG, MPU6050_GYRO_FS_SEL_BIT, MPU6050_GYRO_FS_SEL_LEN, range);
    gyroScale = MPU6050_getGyroScale(range);
}

// ACCEL_CONFIG register
uint8_t MPU6050_getFullScaleAccelRange() {
    I2C_readBits(address, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACCEL_FS_SEL_BIT, MPU6050_ACCEL_FS_SEL_LEN, buffer);

    return buffer[0];
}

void MPU6050_setFullScaleAccelRange(uint8_t range) {
    I2C_writeBits(address, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACCEL_FS_SEL_BIT, MPU6050_ACCEL_FS_SEL_LEN, range);
    accelScale = MPU6050_getAccelScale(range);
}

// INT_PIN_CFG register
bool MPU6050_getI2cBypassEnabled() {
    I2C_readBit(address, MPU6050_RA_INT_PIN_CFG, MPU6050_BYPASS_EN_BIT, buffer);
    return buffer[0];
}

void MPU6050_setI2cBypassEnabled(bool enabled) {
    I2C_writeBit(address, MPU6050_RA_INT_PIN_CFG, MPU6050_BYPASS_EN_BIT, enabled);
}

// USER_CTRL register
bool MPU6050_getDMPEnabled() {
    I2C_readBit(address, MPU6050_RA_USER_CTRL, MPU6050_DMP_EN_BIT, buffer);
    return buffer[0];
}

void MPU6050_setDMPEnabled(bool enabled) {
    I2C_writeBit(address, MPU6050_RA_USER_CTRL, MPU6050_DMP_EN_BIT, enabled);
}

// PWR_MGMT_1 register
void MPU6050_reset() {
    I2C_writeBit(address, MPU6050_RA_PWR_MGMT_1, MPU6050_DEVICE_RESET_BIT, 1);
}
bool MPU6050_getSleepEnabled() {
    I2C_readBit(address, MPU6050_RA_PWR_MGMT_1, MPU6050_SLEEP_BIT, buffer);
    return buffer[0];
}

void MPU6050_setSleepEnabled(bool enabled) {
    I2C_writeBit(address, MPU6050_RA_PWR_MGMT_1, MPU6050_SLEEP_BIT, enabled);
}

uint8_t MPU6050_getClockSource() {
    I2C_readBits(address, MPU6050_RA_PWR_MGMT_1, MPU6050_CLKSEL_BIT, MPU6050_CLKSEL_LEN, buffer);
    return buffer[0];
}

void MPU6050_setClockSource(uint8_t source) {
    I2C_writeBits(address, MPU6050_RA_PWR_MGMT_1, MPU6050_CLKSEL_BIT, MPU6050_CLKSEL_LEN, source);
}

// WHO_AM_I register
uint8_t MPU6050_getDeviceID() {
    I2C_readByte(address, MPU6050_RA_WHO_AM_I, buffer);
    return buffer[0];
}

// Internal
float MPU6050_getGyroScale(uint8_t gyroRange) {
    return 16.4 * pow(2, 3 - gyroRange);
}

float MPU6050_getAccelScale(uint8_t accelRange) {
    return 2048.0 * pow(2, 3 - accelRange);
}