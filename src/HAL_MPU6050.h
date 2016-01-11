#pragma once

#include "config.h"

#ifdef MPU6050_INSTALLED

#include "MPU6050.h"

#include "Accelerometer.h"
#include "Gyroscope.h"
#include "Thermometer.h"

class HAL_MPU6050 : public Accelerometer, public Gyroscope, public Thermometer {
public:
    static HAL_MPU6050& getInstance() {
        static HAL_MPU6050 instance;
        return instance;
    }

    void initialize();
    Vector3 getAcceleration();
    Vector3 getRotation();
    double getTemperature();

private:
    MPU6050 device;
    double gyroScale;
    double accelScale;
};

#endif // MPU6050_INSTALLED
