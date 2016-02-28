// Define which sensors are attached
#define SENSORS_MPU9150_ATTACHED

#include <Sensors.h>

void setup() {
    // Activate serial port (for debug printing)
    Serial.begin(115200);

    // Activate high-speed i2c
    Wire.setSpeed(CLOCK_SPEED_400KHZ);
    Wire.begin();

    // Initialize devices
    Sensors::initialize();
}

void loop() {
    Accelerometer *accelerometer = Sensors::getAccelerometer();
    if(accelerometer) {
        Vector3 a = accelerometer->getAcceleration();
        Serial.printlnf("Acceleration (m/s^2)  %+7.3f, %+7.3f, %+7.3f", a.x, a.y, a.z);
    }

    Barometer *barometer = Sensors::getBarometer();
    if(barometer) {
        float p = barometer->getPressure();
        Serial.printlnf("Pressure (hPa)        %+7.3f", p);

        float a = barometer->getAltitude();
        Serial.printlnf("Altitude (m)          %+7.3f", a);
    }

    Gyroscope *gyroscope = Sensors::getGyroscope();
    if(gyroscope) {
        Vector3 g = gyroscope->getRotation();
        Serial.printlnf("Rotation (rad/s)      %+7.3f, %+7.3f, %+7.3f", g.x, g.y, g.z);
    }

    Magnetometer *magnetometer = Sensors::getMagnetometer();
    if(magnetometer) {
        Vector3 m = magnetometer->getMagneticField();
        Serial.printlnf("Magnetic Field (uT)   %+7.3f, %+7.3f, %+7.3f", m.x, m.y, m.z);

        float azimuth = magnetometer->getAzimuth();
        Serial.printlnf("Azimuth (deg)         %+7.3f", azimuth);
    }

    Thermometer *thermometer = Sensors::getThermometer();
    if(thermometer) {
        float t = thermometer->getTemperature();
        Serial.printlnf("Temperature (C)       %+7.3f", t);
    }

    delay(50);
}
