#pragma once

#include "Accelerometer.h"
#include "Barometer.h"
#include "Gyroscope.h"
#include "Magnetometer.h"
#include "Thermometer.h"

// MPU9150 Accelerometer, Gyroscope and Magnetometer
// The MPU9150 combines an MPU6050 and AK8975 in one chip
#ifdef SENSORS_MPU9150_ATTACHED
    #define SENSORS_MPU6050_ATTACHED
    #define SENSORS_AK8975_ATTACHED
#endif

// MPU9250 Accelerometer, Gyroscope and Magnetometer
// The MPU9250 combines an MPU6500 and AK8963 in one chip
#ifdef SENSORS_MPU9250_ATTACHED
    #define SENSORS_MPU6500_ATTACHED
    #define SENSORS_AK8963_ATTACHED
#endif

// MPU6500 Accelerometer and Gyroscope
// The MPU6500 is both supported by the MPU6050 driver
#ifdef SENSORS_MPU6500_ATTACHED
    #define SENSORS_MPU6050_ATTACHED
#endif

// BMP180 Barometer and Thermometer
// The BMP180 is supported by the BMP085 driver
#ifdef SENSORS_BMP180_ATTACHED
    #define SENSORS_BMP085_ATTACHED
#endif

// AK8963 Magnetometer
#ifdef SENSORS_AK8963_ATTACHED
    #include "AK8963.h"
    #define MAGNETOMETER_ATTACHED
#endif

// BMP085 Barometer and Thermometer
#ifdef SENSORS_BMP085_ATTACHED
    #include "BMP085.h"
    #define BAROMETER_ATTACHED
    #define THERMOMETER_ATTACHED
#endif

// HMC5883L Magnetometer
#ifdef SENSORS_HMC5883L_ATTACHED
    #include "HMC5883L.h"
    #define MAGNETOMETER_ATTACHED
#endif

// MPU6050 Accelerometer and Gyroscope
#ifdef SENSORS_MPU6050_ATTACHED
    #include "MPU6050.h"
    #define ACCELEROMETER_ATTACHED
    #define GYROSCOPE_ATTACHED
#endif

class Sensors {
public:
    // Initialize attached sensors
    // Only call this after enabling and waking up the I2C bus
    static void initialize() {
        #ifdef SENSORS_AK8963_ATTACHED
        AK8963::getInstance().initialize();
        #endif

        #ifdef SENSORS_BMP085_ATTACHED
        BMP085::getInstance().initialize();
        #endif

        #ifdef SENSORS_HMC5883L_ATTACHED
        HMC5883L::getInstance().initialize();
        #endif

        #ifdef SENSORS_MPU6050_ATTACHED
        MPU6050::getInstance().initialize();
        #endif
    }

    static Accelerometer *getAccelerometer() {
        #ifdef SENSORS_MPU6050_ATTACHED
        return &MPU6050::getInstance();
        #else
        return NULL;
        #endif
    }

    static Barometer *getBarometer() {
        #ifdef SENSORS_BMP085_ATTACHED
        return &BMP085::getInstance();
        #else
        return NULL;
        #endif
    }

    static Gyroscope *getGyroscope() {
        #ifdef SENSORS_MPU6050_ATTACHED
        return &MPU6050::getInstance();
        #else
        return NULL;
        #endif
    }

    static Magnetometer *getMagnetometer() {
        #if defined(SENSORS_AK8963_ATTACHED)
        return &AK8963::getInstance();
        #elif defined(SENSORS_HMC5883L_ATTACHED)
        return &HMC5883L::getInstance();
        #else
        return NULL;
        #endif
    }

    static Thermometer *getThermometer() {
        #ifdef SENSORS_BMP085_ATTACHED
        return &BMP085::getInstance();
        #else
        return NULL;
        #endif
    }
};
