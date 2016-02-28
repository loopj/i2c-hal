#pragma once

#include "Accelerometer.h"
#include "Barometer.h"
#include "Gyroscope.h"
#include "Magnetometer.h"
#include "Thermometer.h"

// The MPU9150 combines an MPU6050 and AK8975 in one chip
#ifdef SENSOR_ATTACHED_MPU9150
    #define SENSOR_ATTACHED_MPU6050
    #define SENSOR_ATTACHED_AK8975
#endif

// The MPU9150 combines an MPU6500 and AK8963 in one chip
#ifdef SENSOR_ATTACHED_MPU9250
    #define SENSOR_ATTACHED_MPU6500
    #define SENSOR_ATTACHED_AK8963
#endif

#ifdef SENSOR_ATTACHED_AK8963
    #include "AK8963.h"
#endif

// The BMP085 and BMP180 are both supported by the BMP085 driver
#if defined(SENSOR_ATTACHED_BMP085) || defined(SENSOR_ATTACHED_BMP180)
    #include "BMP085.h"
#endif

#ifdef SENSOR_ATTACHED_HMC5883L
    #include "HMC5883L.h"
#endif

// The MPU6050 and MPU6500 are both supported by the MPU6050 driver
#if defined(SENSOR_ATTACHED_MPU6050) || defined(SENSOR_ATTACHED_MPU6500)
    #include "MPU6050.h"
#endif

class Sensors {
public:
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
        #if defined(SENSOR_ATTACHED_MPU6050)
        return &MPU6050::getInstance();
        #else
        return NULL;
        #endif
    }

    static Barometer *getBarometer() {
        #if defined(SENSOR_ATTACHED_BMP085)
        return &BMP085::getInstance();
        #else
        return NULL;
        #endif
    }

    static Gyroscope *getGyroscope() {
        #if defined(SENSOR_ATTACHED_MPU6050)
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
        #if defined(SENSOR_ATTACHED_BMP085)
        return &BMP085::getInstance();
        #else
        return NULL;
        #endif
    }
};
