#pragma once

#include "config.h"

#ifdef MPU6050_INSTALLED

#include "Accelerometer.h"
#include "Gyroscope.h"
#include "MPU6050.h"

class HAL_MPU6050 : public Accelerometer, public Gyroscope {
public:
    static HAL_MPU6050& getInstance() {
        static HAL_MPU6050 instance;
        return instance;
    }

    void initialize();
    void groundCalibrate();
    Vector3 getAcceleration();
    Vector3 getRotation();

private:
    MPU6050 device;
    double gyroScale;
    double accelScale;
};

#endif // MPU6050_INSTALLED
