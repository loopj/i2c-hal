#pragma once

#include <math.h>
#include <stdint.h>

#include "Accelerometer.h"
#include "Gyroscope.h"
#include "I2C.h"
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

void MPU6050_initialize(uint8_t deviceAddress);
bool MPU6050_testConnection();

// ACCEL_XOUT register
Vector3 MPU6050_getAcceleration();

// GYRO_XOUT register
Vector3 MPU6050_getRotation();

// GYRO_CONFIG register
uint8_t MPU6050_getFullScaleGyroRange();
void MPU6050_etFullScaleGyroRange(uint8_t range);

// ACCEL_CONFIG register
uint8_t MPU6050_getFullScaleAccelRange();
void MPU6050_setFullScaleAccelRange(uint8_t range);

// INT_PIN_CFG register
bool MPU6050_getI2cBypassEnabled();
void MPU6050_setI2cBypassEnabled(bool enabled);

// USER_CTRL register
bool MPU6050_getDMPEnabled();
void MPU6050_setDMPEnabled(bool enabled);

// PWR_MGMT_1 register
void MPU6050_reset();
bool MPU6050_getSleepEnabled();
void MPU6050_setSleepEnabled(bool enabled);
uint8_t MPU6050_getClockSource();
void MPU6050_setClockSource(uint8_t source);

// WHO_AM_I register
uint8_t MPU6050_getDeviceID();