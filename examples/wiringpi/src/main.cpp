#include <stdio.h>
#include <wiringPi.h>

#include "Sensors.h"

int main() {
    wiringPiSetup();

    while(true) {
        printf("tick\n");
        delay(50);
    }
}
