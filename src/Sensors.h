#pragma once

#include "Accelerometer.h"
#include "Barometer.h"
#include "Gyroscope.h"
#include "Magnetometer.h"
#include "Thermometer.h"

#ifdef AK8963_INSTALLED
#include "AK8963.h"
#endif

#ifdef BMP085_INSTALLED
#include "BMP085.h"
#endif

#ifdef HMC5883L_INSTALLED
#include "HMC5883L.h"
#endif

#ifdef MPU6500_INSTALLED
#include "MPU6500.h"
#endif

class Sensors {
public:
    static void initialize() {
        #ifdef AK8963_INSTALLED
        AK8963::getInstance().initialize();
        #endif

        #ifdef BMP085_INSTALLED
        BMP085::getInstance().initialize();
        #endif

        #ifdef HMC5883L_INSTALLED
        HMC5883L::getInstance().initialize();
        #endif

        #ifdef MPU6500_INSTALLED
        MPU6500::getInstance().initialize();
        #endif
    }

    static Accelerometer *getAccelerometer() {
        #if defined(MPU6500_INSTALLED)
        return &MPU6500::getInstance();
        #else
        return NULL;
        #endif
    }

    static Barometer *getBarometer() {
        #if defined(BMP085_INSTALLED)
        return &BMP085::getInstance();
        #else
        return NULL;
        #endif
    }

    static Gyroscope *getGyroscope() {
        #if defined(MPU6500_INSTALLED)
        return &MPU6500::getInstance();
        #else
        return NULL;
        #endif
    }

    static Magnetometer *getMagnetometer() {
        #if defined(AK8963_INSTALLED)
        return &AK8963::getInstance();
        #elif defined(HMC5883L_INSTALLED)
        return &HMC5883L::getInstance();
        #else
        return NULL;
        #endif
    }

    static Thermometer *getThermometer() {
        #if defined(BMP085_INSTALLED)
        return &BMP085::getInstance();
        #else
        return NULL;
        #endif
    }
};
