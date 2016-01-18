#include "config.h"
#include "Sensors.h"

#ifdef MPU6500_INSTALLED
#include "MPU6500.h"
#endif

#ifdef AK8963_INSTALLED
#include "AK8963.h"
#endif

void Sensors::initialize() {
    #ifdef MPU6500_INSTALLED
    MPU6500::getInstance().initialize();
    #endif

    #ifdef AK8963_INSTALLED
    AK8963::getInstance().initialize();
    #endif
}

Accelerometer *Sensors::getAccelerometer() {
    #ifdef MPU6500_INSTALLED
    return &MPU6500::getInstance();
    #else
    return NULL;
    #endif
}

Barometer *Sensors::getBarometer() {
    return NULL;
}

Gyroscope *Sensors::getGyroscope() {
    #ifdef MPU6500_INSTALLED
    return &MPU6500::getInstance();
    #else
    return NULL;
    #endif
}

Magnetometer *Sensors::getMagnetometer() {
    #ifdef AK8963_INSTALLED
    return &AK8963::getInstance();
    #else
    return NULL;
    #endif
}

Thermometer *Sensors::getThermometer() {
    return NULL;
}
