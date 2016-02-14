#include <stdio.h>
#include <wiringPi.h>

#include "Sensors.h"

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

        delay(50);
    }
}
