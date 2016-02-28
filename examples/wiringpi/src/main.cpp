// Define which sensors are attached
#define SENSORS_BMP085_ATTACHED
#define SENSORS_HMC5883L_ATTACHED
#define SENSORS_MPU6050_ATTACHED

#include <stdio.h>
#include <wiringPi.h>
#include <Sensors.h>

int main() {
    // Initialize WiringPi pins
    wiringPiSetup();

    // Initialize devices
    Sensors::initialize();

    while(true) {
        Accelerometer *accelerometer = Sensors::getAccelerometer();
        if(accelerometer) {
            Vector3 a = accelerometer->getAcceleration();
            printf("Acceleration (m/s^2)  %+7.3f, %+7.3f, %+7.3f\n", a.x, a.y, a.z);
        }

        Barometer *barometer = Sensors::getBarometer();
        if(barometer) {
            float p = barometer->getPressure();
            printf("Pressure (hPa)        %+7.3f\n", p);

            float a = barometer->getAltitude();
            printf("Altitude (m)          %+7.3f\n", a);
        }

        Gyroscope *gyroscope = Sensors::getGyroscope();
        if(gyroscope) {
            Vector3 g = gyroscope->getRotation();
            printf("Rotation (rad/s)      %+7.3f, %+7.3f, %+7.3f\n", g.x, g.y, g.z);
        }

        Magnetometer *magnetometer = Sensors::getMagnetometer();
        if(magnetometer) {
            Vector3 m = magnetometer->getMagneticField();
            printf("Magnetic Field (uT)   %+7.3f, %+7.3f, %+7.3f\n", m.x, m.y, m.z);

            float azimuth = magnetometer->getAzimuth();
            printf("Azimuth (deg)         %+7.3f\n", azimuth);
        }

        Thermometer *thermometer = Sensors::getThermometer();
        if(thermometer) {
            float t = thermometer->getTemperature();
            printf("Temperature (C)       %+7.3f\n", t);
        }

        delay(50);
    }
}
