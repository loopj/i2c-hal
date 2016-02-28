// Define which sensors are attached
#define SENSORS_BMP085_ATTACHED

// Debug printing
#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp8266.h>
#include <Sensors.h>
#include <Wire.h>

// Blynk auth token (from the blynk app)
char blynkToken[] = "your-blynk-token";

// WiFi access point credentials
char ssid[] = "your-wifi-ssid";
char password[] = "your-wifi-password";

void setup() {
    // Activate serial port (for debug printing)
    Serial.begin(9600);

    // Activate i2c
    Wire.begin();

    // Initialize WiFi and connect to Blynk
    Blynk.begin(blynkToken, ssid, password);

    // Initialize devices
    Sensors::initialize();
}

// When Blynk requests the value of virtual pin 0, send back the air pressure
BLYNK_READ(V0) {
    Barometer *barometer = Sensors::getBarometer();
    if(barometer) {
        float p = barometer->getPressure();
        Blynk.virtualWrite(V0, p);
    }
}

// When Blynk requests the value of virtual pin 1, send back the temperature
BLYNK_READ(V1) {
    Thermometer *thermometer = Sensors::getThermometer();
    if(thermometer) {
        float t = thermometer->getTemperature();
        Blynk.virtualWrite(V1, t);
    }
}

void loop() {
    Blynk.run();
}
