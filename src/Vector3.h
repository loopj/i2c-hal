#pragma once

#include <math.h>

struct Vector3 {
    union {
        float v[3];
        struct {
            float x;
            float y;
            float z;
        };
        struct {
            union {
                float azimuth;
                float yaw;
            };
            float pitch;
            float roll;
        };
    };

    Vector3() {
        x = 0;
        y = 0;
        z = 0;
    }

    float norm() {
        return sqrt(x*x + y*y + z*z);
    }

    void normalize() {
        float n = norm();

        if(n > 0) {
            x /= n;
            y /= n;
            z /= n;
        }
    }
};
