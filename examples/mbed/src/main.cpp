// Define which sensors are attached
#define SENSORS_BMP085_ATTACHED
#define SENSORS_HMC5883L_ATTACHED
#define SENSORS_MPU6050_ATTACHED

#include "mbed.h"
#include "USBSerial.h"
#include "Sensors.h"

USBSerial serial;

// Quick and dirty way to print floats
void printFloat(float flt, int precision=2) {
    serial.printf("%d.%d", (int)flt, abs((int)((flt - (int)flt) * pow(10,precision))));
}

int main() {
    // Initialize devices
    Sensors::initialize();

    while(1) {
        Accelerometer *accelerometer = Sensors::getAccelerometer();
        if(accelerometer) {
            Vector3 a = accelerometer->getAcceleration();
            serial.printf("Acceleration (m/s^2)  ");
            printFloat(a.x); serial.printf(", ");
            printFloat(a.y); serial.printf(", ");
            printFloat(a.z); serial.printf("\n");
        }

        Barometer *barometer = Sensors::getBarometer();
        if(barometer) {
            float p = barometer->getPressure();
            serial.printf("Pressure (hPa)        ");
            printFloat(p); serial.printf("\n");

            float a = barometer->getAltitude();
            serial.printf("Altitude (m)          ");
            printFloat(a); serial.printf("\n");
        }

        Gyroscope *gyroscope = Sensors::getGyroscope();
        if(gyroscope) {
            Vector3 g = gyroscope->getRotation();
            serial.printf("Rotation (rad/s)      ");
            printFloat(g.x); serial.printf(", ");
            printFloat(g.y); serial.printf(", ");
            printFloat(g.z); serial.printf("\n");
        }

        Magnetometer *magnetometer = Sensors::getMagnetometer();
        if(magnetometer) {
            Vector3 m = magnetometer->getMagneticField();
            serial.printf("Magnetic Field (uT)   ");
            printFloat(m.x); serial.printf(", ");
            printFloat(m.y); serial.printf(", ");
            printFloat(m.z); serial.printf("\n");

            float azimuth = magnetometer->getAzimuth();
            serial.printf("Azimuth (deg)         ");
            printFloat(azimuth); serial.printf("\n");
        }

        Thermometer *thermometer = Sensors::getThermometer();
        if(thermometer) {
            float t = thermometer->getTemperature();
            serial.printf("Temperature (C)       ");
            printFloat(t); serial.printf("\n");
        }

        wait_ms(50);
    }
}
