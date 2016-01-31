#pragma once

#include "Sensor_Config.h"

#include "Accelerometer.h"
#include "Barometer.h"
#include "Gyroscope.h"
#include "Magnetometer.h"
#include "Thermometer.h"

class Sensors {
public:
    static void initialize();

    static Accelerometer *getAccelerometer();
    static Barometer *getBarometer();
    static Gyroscope *getGyroscope();
    static Magnetometer *getMagnetometer();
    static Thermometer *getThermometer();
};
