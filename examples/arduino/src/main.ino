// Define which sensors are attached
#define SENSORS_BMP180_ATTACHED
#define SENSORS_HMC5883L_ATTACHED
#define SENSORS_MPU6050_ATTACHED

#include <Sensors.h>
#include <Wire.h>

void setup() {
    // Activate serial port (for debug printing)
    Serial.begin(9600);

    // Activate i2c
    Wire.begin();

    // Initialize devices
    Sensors::initialize();
}

void loop() {
    Accelerometer *accelerometer = Sensors::getAccelerometer();
    if(accelerometer) {
        Vector3 a = accelerometer->getAcceleration();
        Serial.print("Acceleration (m/s^2)  ");
        Serial.print(a.x);
        Serial.print(", ");
        Serial.print(a.y);
        Serial.print(", ");
        Serial.println(a.z);
    }

    Barometer *barometer = Sensors::getBarometer();
    if(barometer) {
        float p = barometer->getPressure();
        Serial.print("Pressure (hPa)        ");
        Serial.println(p);

        float a = barometer->getAltitude();
        Serial.print("Altitude (m)          ");
        Serial.println(a);
    }

    Gyroscope *gyroscope = Sensors::getGyroscope();
    if(gyroscope) {
        Vector3 g = gyroscope->getRotation();
        Serial.print("Rotation (rad/s)      ");
        Serial.print(g.x);
        Serial.print(", ");
        Serial.print(g.y);
        Serial.print(", ");
        Serial.println(g.z);
    }

    Magnetometer *magnetometer = Sensors::getMagnetometer();
    if(magnetometer) {
        Vector3 m = magnetometer->getMagneticField();
        Serial.print("Magnetic Field (uT)   ");
        Serial.print(m.x);
        Serial.print(", ");
        Serial.print(m.y);
        Serial.print(", ");
        Serial.println(m.z);

        float azimuth = magnetometer->getAzimuth();
        Serial.print("Azimuth (deg)         ");
        Serial.println(azimuth);
    }

    Thermometer *thermometer = Sensors::getThermometer();
    if(thermometer) {
        float t = thermometer->getTemperature();
        Serial.print("Temperature (C)       ");
        Serial.println(t);
    }

    delay(50);
}
