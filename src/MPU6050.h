#pragma once

#include <math.h>
#include <stdint.h>

#include "Accelerometer.h"
#include "Gyroscope.h"
#include "I2CDevice.h"
#include "Vector3.h"

// Device info
#define MPU6050_ADDRESS_AD0_LOW     0x68
#define MPU6050_ADDRESS_AD0_HIGH    0x69
#define MPU6050_DEFAULT_ADDRESS     MPU6050_ADDRESS_AD0_LOW

// Device IDs for WHO_AM_I register
#define MPU6050_DEVICE_ID           0x34
#define MPU6500_DEVICE_ID           0x70
#define MPU9150_DEVICE_ID           0x68
#define MPU9250_DEVICE_ID           0x71

// Register map
enum {
    MPU6050_RA_GYRO_CONFIG         = 0x1B,
    MPU6050_RA_ACCEL_CONFIG        = 0x1C,
    MPU6050_RA_INT_PIN_CFG         = 0x37,
    MPU6050_RA_ACCEL_XOUT_H        = 0x3B,
    MPU6050_RA_TEMP_OUT_H          = 0x41,
    MPU6050_RA_GYRO_XOUT_H         = 0x43,
    MPU6050_RA_USER_CTRL           = 0x6A,
    MPU6050_RA_PWR_MGMT_1          = 0x6B,
    MPU6050_RA_WHO_AM_I            = 0x75
};

// GYRO_CONFIG
#define MPU6050_GYRO_FS_SEL_BIT     4
#define MPU6050_GYRO_FS_SEL_LEN     2

// GYRO_CONFIG FS_SEL
#define MPU6050_GYRO_FS_250         0x00
#define MPU6050_GYRO_FS_500         0x01
#define MPU6050_GYRO_FS_1000        0x02
#define MPU6050_GYRO_FS_2000        0x03

// ACCEL_CONFIG
#define MPU6050_ACCEL_FS_SEL_BIT    4
#define MPU6050_ACCEL_FS_SEL_LEN    2

// ACCEL_CONFIG AFS_SEL
#define MPU6050_ACCEL_FS_2          0x00
#define MPU6050_ACCEL_FS_4          0x01
#define MPU6050_ACCEL_FS_8          0x02
#define MPU6050_ACCEL_FS_16         0x03

// INT_PIN_CFG
#define MPU6050_BYPASS_EN_BIT       1

// USER_CTRL
#define MPU6050_DMP_EN_BIT          7
#define MPU6050_FIFO_EN_BIT         6

// PWR_MGMT_1
#define MPU6050_DEVICE_RESET_BIT    7
#define MPU6050_SLEEP_BIT           6
#define MPU6050_CLKSEL_BIT          2
#define MPU6050_CLKSEL_LEN          3
#define MPU6050_CLOCK_INTERNAL      0x00
#define MPU6050_CLOCK_PLL           0x01
#define MPU6050_CLOCK_KEEP_RESET    0x07

class MPU6050 : public I2CDevice, public Accelerometer, public Gyroscope {
public:
    static MPU6050& getInstance() {
        static MPU6050 instance;
        return instance;
    }

    // Initialization
    MPU6050(uint8_t address = MPU6050_DEFAULT_ADDRESS) : I2CDevice(address) {

    }

    void initialize() {
        // Wake up the device
        setSleepEnabled(false);

        // Use the most accurate clock source
        setClockSource(MPU6050_CLOCK_PLL);

        // Set the sensitivity to max on gyro and accel
        setFullScaleGyroRange(MPU6050_GYRO_FS_250);
        setFullScaleAccelRange(MPU6050_ACCEL_FS_2);

        // Allow direct I2C access to devices connected to the MPU6050 aux bus
        setI2cBypassEnabled(true);

        // Calculate the scale factors from the configured ranges
        accelScale = getAccelScale(getFullScaleAccelRange());
        gyroScale = getGyroScale(getFullScaleGyroRange());
    }

    bool testConnection() {
        switch(getDeviceID()) {
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
    Vector3 getAcceleration() {
        Vector3 acceleration;

        // Convert raw data into signed 16-bit data
        int16_t rawAccel[3];
        readWords(MPU6050_RA_ACCEL_XOUT_H, 3, (uint16_t *)rawAccel);

        // Apply accelerometer scale to get Gs, convert to m/s^2
        acceleration.x = (float)rawAccel[0]/accelScale * STANDARD_GRAVITY;
        acceleration.y = (float)rawAccel[1]/accelScale * STANDARD_GRAVITY;
        acceleration.z = (float)rawAccel[2]/accelScale * STANDARD_GRAVITY;

        return acceleration;
    }

    // Gyroscope
    Vector3 getRotation() {
        Vector3 rotation;

        // Convert raw data into signed 16-bit data
        int16_t rawRotation[3];
        readWords(MPU6050_RA_GYRO_XOUT_H, 3, (uint16_t *)rawRotation);

        // Apply gyroscope scale to get deg/s, convert to rad/s
        rotation.x = (float)rawRotation[0]/gyroScale * M_PI/180.0;
        rotation.y = (float)rawRotation[1]/gyroScale * M_PI/180.0;
        rotation.z = (float)rawRotation[2]/gyroScale * M_PI/180.0;

        return rotation;
    }

    // GYRO_CONFIG register
    uint8_t getFullScaleGyroRange() {
        readBits(MPU6050_RA_GYRO_CONFIG, MPU6050_GYRO_FS_SEL_BIT, MPU6050_GYRO_FS_SEL_LEN, buffer);

        return buffer[0];
    }

    void setFullScaleGyroRange(uint8_t range) {
        writeBits(MPU6050_RA_GYRO_CONFIG, MPU6050_GYRO_FS_SEL_BIT, MPU6050_GYRO_FS_SEL_LEN, range);
        gyroScale = getGyroScale(range);
    }

    // ACCEL_CONFIG register
    uint8_t getFullScaleAccelRange() {
        readBits(MPU6050_RA_ACCEL_CONFIG, MPU6050_ACCEL_FS_SEL_BIT, MPU6050_ACCEL_FS_SEL_LEN, buffer);

        return buffer[0];
    }

    void setFullScaleAccelRange(uint8_t range) {
        writeBits(MPU6050_RA_ACCEL_CONFIG, MPU6050_ACCEL_FS_SEL_BIT, MPU6050_ACCEL_FS_SEL_LEN, range);
        accelScale = getAccelScale(range);
    }

    // INT_PIN_CFG register
    bool getI2cBypassEnabled() {
        readBit(MPU6050_RA_INT_PIN_CFG, MPU6050_BYPASS_EN_BIT, buffer);
        return buffer[0];
    }

    void setI2cBypassEnabled(bool enabled) {
        writeBit(MPU6050_RA_INT_PIN_CFG, MPU6050_BYPASS_EN_BIT, enabled);
    }

    // USER_CTRL register
    bool getDMPEnabled() {
        readBit(MPU6050_RA_USER_CTRL, MPU6050_DMP_EN_BIT, buffer);
        return buffer[0];
    }

    void setDMPEnabled(bool enabled) {
        writeBit(MPU6050_RA_USER_CTRL, MPU6050_DMP_EN_BIT, enabled);
    }

    // PWR_MGMT_1 register
    void reset() {
        writeBit(MPU6050_RA_PWR_MGMT_1, MPU6050_DEVICE_RESET_BIT, 1);
    }
    bool getSleepEnabled() {
        readBit(MPU6050_RA_PWR_MGMT_1, MPU6050_SLEEP_BIT, buffer);
        return buffer[0];
    }

    void setSleepEnabled(bool enabled) {
        writeBit(MPU6050_RA_PWR_MGMT_1, MPU6050_SLEEP_BIT, enabled);
    }

    uint8_t getClockSource() {
        readBits(MPU6050_RA_PWR_MGMT_1, MPU6050_CLKSEL_BIT, MPU6050_CLKSEL_LEN, buffer);
        return buffer[0];
    }

    void setClockSource(uint8_t source) {
        writeBits(MPU6050_RA_PWR_MGMT_1, MPU6050_CLKSEL_BIT, MPU6050_CLKSEL_LEN, source);
    }

    // WHO_AM_I register
    uint8_t getDeviceID() {
        readByte(MPU6050_RA_WHO_AM_I, buffer);
        return buffer[0];
    }

protected:
    float accelScale;
    float gyroScale;

    float getGyroScale(uint8_t gyroRange) {
        return 16.4 * pow(2, 3 - gyroRange);
    }

    float getAccelScale(uint8_t accelRange) {
        return 2048.0 * pow(2, 3 - accelRange);
    }
};
