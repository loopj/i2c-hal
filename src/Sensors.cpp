#include "Sensors.h"

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

void Sensors::initialize() {
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

Accelerometer *Sensors::getAccelerometer() {
    #if defined(MPU6500_INSTALLED)
    return &MPU6500::getInstance();
    #else
    return nullptr;
    #endif
}

Barometer *Sensors::getBarometer() {
    #if defined(BMP085_INSTALLED)
    return &BMP085::getInstance();
    #else
    return nullptr;
    #endif
}

Gyroscope *Sensors::getGyroscope() {
    #if defined(MPU6500_INSTALLED)
    return &MPU6500::getInstance();
    #else
    return nullptr;
    #endif
}

Magnetometer *Sensors::getMagnetometer() {
    #if defined(AK8963_INSTALLED)
    return &AK8963::getInstance();
    #elif defined(HMC5883L_INSTALLED)
    return &HMC5883L::getInstance();
    #else
    return nullptr;
    #endif
}

Thermometer *Sensors::getThermometer() {
    #if defined(BMP085_INSTALLED)
    return &BMP085::getInstance();
    #else
    return nullptr;
    #endif
}
