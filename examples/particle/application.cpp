#include "application.h"

void setup() {
    Serial.begin(115200);
    delay(5000);
}

void loop() {
    Serial.println("HELLO!");
    delay(500);
}
