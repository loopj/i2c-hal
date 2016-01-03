#pragma once

#include "config.h"

#ifdef HMC5883L_INSTALLED

#include "Compass.h"
#include "HMC5883L.h"

class HAL_HMC5883L : public Compass {
public:
    static HAL_HMC5883L& getInstance() {
        static HAL_HMC5883L instance;
        return instance;
    }

    void initialize();
    Vector3 getHeading();

private:
    HMC5883L device;
    float magScale;
};

#endif // HMC5883L_INSTALLED
