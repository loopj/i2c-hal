#include "config.h"
#include "Sensors.h"

#ifdef MPU6500_INSTALLED
#include "MPU6500.h"
#endif

#ifdef AK8963_INSTALLED
#include "AK8963.h"
#endif

#ifdef HMC5883L_INSTALLED
#include "HMC5883L.h"
#endif

void Sensors::initialize() {
    #ifdef MPU6500_INSTALLED
    MPU6500::getInstance().initialize();
    #endif

    #ifdef AK8963_INSTALLED
    AK8963::getInstance().initialize();
    #endif

    #ifdef HMC5883L_INSTALLED
    HMC5883L::getInstance().initialize();
    #endif
}

Accelerometer *Sensors::getAccelerometer() {
    #if defined(MPU6500_INSTALLED)
    return &MPU6500::getInstance();
    #else
    return NULL;
    #endif
}

Barometer *Sensors::getBarometer() {
    return NULL;
}

Gyroscope *Sensors::getGyroscope() {
    #if defined(MPU6500_INSTALLED)
    return &MPU6500::getInstance();
    #else
    return NULL;
    #endif
}

Magnetometer *Sensors::getMagnetometer() {
    #if defined(AK8963_INSTALLED)
    return &AK8963::getInstance();
    #elif defined(HMC5883L_INSTALLED)
    return &HMC5883L::getInstance();
    #else
    return NULL;
    #endif
}

Thermometer *Sensors::getThermometer() {
    return NULL;
}
