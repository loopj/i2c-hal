#pragma once

#include "Accelerometer.h"
#include "Barometer.h"
#include "Gyroscope.h"
#include "Magnetometer.h"
#include "Thermometer.h"

#ifdef SENSOR_ATTACHED_AK8963
#include "AK8963.h"
#endif

#ifdef SENSOR_ATTACHED_BMP085
#include "BMP085.h"
#endif

#ifdef SENSOR_ATTACHED_HMC5883L
#include "HMC5883L.h"
#endif

#ifdef SENSOR_ATTACHED_MPU6500
#include "MPU6500.h"
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

        #ifdef SENSOR_ATTACHED_MPU6500
        MPU6500::getInstance().initialize();
        #endif
    }

    static Accelerometer *getAccelerometer() {
        #if defined(SENSOR_ATTACHED_MPU6500)
        return &MPU6500::getInstance();
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
        #if defined(SENSOR_ATTACHED_MPU6500)
        return &MPU6500::getInstance();
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
