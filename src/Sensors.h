#pragma once

#include "Accelerometer.h"
#include "Barometer.h"
#include "Gyroscope.h"
#include "Magnetometer.h"
#include "Thermometer.h"

// MPU9150 Accelerometer, Gyroscope and Magnetometer
// The MPU9150 combines an MPU6050 and AK8975 in one chip
#ifdef SENSOR_ATTACHED_MPU9150
    #define SENSOR_ATTACHED_MPU6050
    #define SENSOR_ATTACHED_AK8975
#endif

// MPU9250 Accelerometer, Gyroscope and Magnetometer
// The MPU9250 combines an MPU6500 and AK8963 in one chip
#ifdef SENSOR_ATTACHED_MPU9250
    #define SENSOR_ATTACHED_MPU6500
    #define SENSOR_ATTACHED_AK8963
#endif

// MPU6500 Accelerometer and Gyroscope
// The MPU6500 is both supported by the MPU6050 driver
#ifdef SENSOR_ATTACHED_MPU6500
    #define SENSOR_ATTACHED_MPU6050
#endif

// BMP180 Barometer and Thermometer
// The BMP180 is supported by the BMP085 driver
#ifdef SENSOR_ATTACHED_BMP180
    #define SENSOR_ATTACHED_BMP085
#endif

// AK8963 Magnetometer
#ifdef SENSOR_ATTACHED_AK8963
    #include "AK8963.h"
#endif

// BMP085 Barometer and Thermometer
#ifdef SENSOR_ATTACHED_BMP085
    #include "BMP085.h"
#endif

// HMC5883L Magnetometer
#ifdef SENSOR_ATTACHED_HMC5883L
    #include "HMC5883L.h"
#endif

// MPU6050 Accelerometer and Gyroscope
#ifdef SENSOR_ATTACHED_MPU6050
    #include "MPU6050.h"
#endif

class Sensors {
public:
    // Initialize attached sensors
    // Only call this after enabling and waking up the I2C bus
    static void initialize() {
        #ifdef SENSOR_ATTACHED_AK8963
        AK8963::getInstance().initialize();
        #endif

        #ifdef SENSOR_ATTACHED_BMP085
        BMP085::getInstance().initialize();
        #endif

        #ifdef SENSOR_ATTACHED_HMC5883L
        HMC5883L::getInstance().initialize();
        #endif

        #ifdef SENSOR_ATTACHED_MPU6050
        MPU6050::getInstance().initialize();
        #endif
    }

    static Accelerometer *getAccelerometer() {
        #ifdef SENSOR_ATTACHED_MPU6050
        return &MPU6050::getInstance();
        #else
        return NULL;
        #endif
    }

    static Barometer *getBarometer() {
        #ifdef SENSOR_ATTACHED_BMP085
        return &BMP085::getInstance();
        #else
        return NULL;
        #endif
    }

    static Gyroscope *getGyroscope() {
        #ifdef SENSOR_ATTACHED_MPU6050
        return &MPU6050::getInstance();
        #else
        return NULL;
        #endif
    }

    static Magnetometer *getMagnetometer() {
        #if defined(SENSOR_ATTACHED_AK8963)
        return &AK8963::getInstance();
        #elif defined(SENSOR_ATTACHED_HMC5883L)
        return &HMC5883L::getInstance();
        #else
        return NULL;
        #endif
    }

    static Thermometer *getThermometer() {
        #ifdef SENSOR_ATTACHED_BMP085
        return &BMP085::getInstance();
        #else
        return NULL;
        #endif
    }
};
