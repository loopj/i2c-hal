#pragma once

#include "config.h"

#ifdef AK8963_INSTALLED

#include "Compass.h"
#include "AK8963.h"

class HAL_AK8963 : public Compass {
public:
    static HAL_AK8963& getInstance() {
        static HAL_AK8963 instance;
        return instance;
    }

    void initialize();
    Vector3 getHeading();

private:
    AK8963 device;
    double scale;
};

#endif // AK8963_INSTALLED
