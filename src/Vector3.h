#pragma once

struct Vector3 {
    union {
        float v[3];
        struct {
            float x;
            float y;
            float z;
        };
    };

    Vector3() : x(0), y(0), z(0) { }
};
