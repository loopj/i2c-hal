#pragma once

#include "config.h"

#ifdef BMP085_INSTALLED

#include "Barometer.h"
#include "BMP085.h"

class HAL_BMP085 : public Barometer {
public:
    static HAL_BMP085& getInstance() {
        static HAL_BMP085 instance;
        return instance;
    }

    void initialize();
    double getPressure();
    double getAltitude();

private:
    BMP085 device;
};

#endif // BMP085_INSTALLED
