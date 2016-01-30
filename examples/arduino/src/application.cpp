#include "Arduino.h"
#include "Wire.h"

#include "Accelerometer.h"
#include "Barometer.h"
#include "Gyroscope.h"
#include "Magnetometer.h"
#include "Sensors.h"
#include "Vector3.h"

void printlnf(const char *format, ...) {
    char buf[255];
    va_list args;
    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);

    Serial.println(buf);
}

void setup() {
    // Activate serial port (for debug printing)
    Serial.begin(115200);

    delay(5000);
    Serial.println("STARTING");

    // Activate i2c
    Wire.begin();

    // Initialize devices
    Sensors::initialize();
}

void loop() {
    Accelerometer *accelerometer = Sensors::getAccelerometer();
    if(accelerometer) {
        Vector3 a = accelerometer->getAcceleration();
        printlnf("Acceleration (m/s^2)  %+7.3f, %+7.3f, %+7.3f", a.x, a.y, a.z);
    }

    Barometer *barometer = Sensors::getBarometer();
    if(barometer) {
        float p = barometer->getPressure();
        printlnf("Pressure (hPa)        %+7.3f", p);

        float a = barometer->getAltitude();
        printlnf("Altitude (m)          %+7.3f", a);
    }

    Gyroscope *gyroscope = Sensors::getGyroscope();
    if(gyroscope) {
        Vector3 g = gyroscope->getRotation();
        printlnf("Rotation (rad/s)      %+7.3f, %+7.3f, %+7.3f", g.x, g.y, g.z);
    }

    Magnetometer *magnetometer = Sensors::getMagnetometer();
    if(magnetometer) {
        Vector3 m = magnetometer->getMagneticField();
        printlnf("Magnetic Field (uT)   %+7.3f, %+7.3f, %+7.3f", m.x, m.y, m.z);

        float azimuth = magnetometer->getAzimuth();
        printlnf("Azimuth (deg)         %+7.3f", azimuth);
    }

    Thermometer *thermometer = Sensors::getThermometer();
    if(thermometer) {
        float t = thermometer->getTemperature();
        printlnf("Temperature (C)       %+7.3f", t);
    }

    printlnf("Tick");

    delay(50);
}
