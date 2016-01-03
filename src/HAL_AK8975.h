#pragma once

#include "config.h"

#ifdef AK8975_INSTALLED

#include "Compass.h"
#include "AK8975.h"

class HAL_AK8975 : public Compass {
public:
    static HAL_AK8975& getInstance() {
        static HAL_AK8975 instance;
        return instance;
    }

    void initialize();
    Vector3 getHeading();

private:
    AK8975 device;
};

#endif // AK8975_INSTALLED
