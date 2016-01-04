#include "application.h"

#include <stdarg.h>
#define LOGGER_BUFFER_LENGTH 255

#include "Compass.h"
#include "HAL_AK8963.h"
#include "HAL_MPU6050.h"
#include "Vector3.h"

HAL_AK8963 compass;
HAL_MPU6050 accelgyro;

void logger(const char* format, ...) {
    char buffer[LOGGER_BUFFER_LENGTH];
    va_list args;

    va_start(args, format);
    vsnprintf(buffer, LOGGER_BUFFER_LENGTH, format, args);
    va_end(args);

    Serial.println(buffer);
    Serial.flush();
}

void setup() {
    Serial.begin(115200);
    delay(5000);

    // Activate high-speed i2c
    Wire.setSpeed(CLOCK_SPEED_400KHZ);
    Wire.begin();

    accelgyro.initialize();
    compass.initialize();
}

void loop() {
    Vector3 acceleration = accelgyro.getAcceleration();
    logger("Acceleration:   %f, %f, %f", acceleration.x, acceleration.y, acceleration.z);

    Vector3 rotation = accelgyro.getRotation();
    logger("Rotation:       %f, %f, %f", rotation.x, rotation.y, rotation.z);

    Vector3 heading = compass.getHeading();
    logger("Heading:        %f, %f, %f", heading.x, heading.y, heading.z);

    Serial.println();

    delay(100);
}
