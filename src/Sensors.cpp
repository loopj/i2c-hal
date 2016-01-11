#include "config.h"
#include "Sensors.h"

#ifdef AK8963_INSTALLED
#include "HAL_AK8963.h"
#endif

#ifdef AK8975_INSTALLED
#include "HAL_AK8975.h"
#endif

#ifdef BMP085_INSTALLED
#include "HAL_BMP085.h"
#endif

#ifdef HMC5883L_INSTALLED
#include "HAL_HMC5883L.h"
#endif

#ifdef MPU6050_INSTALLED
#include "HAL_MPU6050.h"
#endif

void Sensors::initialize() {
    #ifdef AK8963_INSTALLED
    HAL_AK8963::getInstance().initialize();
    #endif

    #ifdef AK8975_INSTALLED
    HAL_AK8975::getInstance().initialize();
    #endif

    #ifdef BMP085_INSTALLED
    HAL_BMP085::getInstance().initialize();
    #endif

    #ifdef HMC5883L_INSTALLED
    HAL_HMC5883L::getInstance().initialize();
    #endif

    #ifdef MPU6050_INSTALLED
    HAL_MPU6050::getInstance().initialize();
    #endif
}

Accelerometer *Sensors::getAccelerometer() {
    #ifdef MPU6050_INSTALLED
    return &HAL_MPU6050::getInstance();
    #else
    return NULL;
    #endif
}

Barometer *Sensors::getBarometer() {
    #ifdef BMP085_INSTALLED
    return &HAL_BMP085::getInstance();
    #else
    return NULL;
    #endif
}

Gyroscope *Sensors::getGyroscope() {
    #ifdef MPU6050_INSTALLED
    return &HAL_MPU6050::getInstance();
    #else
    return NULL;
    #endif
}

Magnetometer *Sensors::getMagnetometer() {
    #if defined AK8963_INSTALLED
    return &HAL_AK8963::getInstance();
    #elif defined AK8975_INSTALLED
    return &HAL_AK8975::getInstance();
    #elif defined HMC5883L_INSTALLED
    return &HAL_HMC5883L::getInstance();
    #else
    return NULL;
    #endif
}

Thermometer *Sensors::getThermometer() {
    #if defined BMP085_INSTALLED
    return &HAL_BMP085::getInstance();
    #elif defined MPU6050_INSTALLED
    return &HAL_MPU6050::getInstance();
    #else
    return NULL;
    #endif
}
