#pragma once

#include "math.h"

class Vector3 {
public:
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    Vector3() {}

    Vector3(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double norm() {
        return sqrt(x*x + y*y + z*z);
    }

    void normalize() {
        double n = norm();

        if(n > 0) {
            x /= n;
            y /= n;
            z /= n;
        }
    }
};
