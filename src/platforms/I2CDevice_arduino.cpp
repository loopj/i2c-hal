// Platform-specific I2C methods, for Arduino and Particle devices

#if defined(ARDUINO) || defined(SPARK)

#ifdef ARDUINO
    #include "Arduino.h"
    #include <Wire.h>
#endif

#ifdef SPARK
    #include "application.h"
#endif

#include "I2CDevice.h"

int8_t I2CDevice::readBytes(uint8_t regAddr, uint8_t length, uint8_t *data) {
    uint8_t count = 0;

    Wire.beginTransmission(address);
    Wire.write(regAddr);
    Wire.endTransmission();

    Wire.beginTransmission(address);
    Wire.requestFrom(address, length);

    while(Wire.available()) {
        data[count] = Wire.read();
        count++;
    }

    Wire.endTransmission();

    return count;
}

int8_t I2CDevice::readWords(uint8_t regAddr, uint8_t length, uint16_t *data) {
    uint8_t count = 0;

    Wire.beginTransmission(address);
    Wire.write(regAddr);
    Wire.endTransmission();

    Wire.beginTransmission(address);
    Wire.requestFrom(address, (uint8_t)(length * 2)); // length=words, this wants bytes

    bool msb = true;
    while(Wire.available()) {
        if (msb) {
            data[count] = Wire.read() << 8;
        } else {
            data[count] |= Wire.read();
            count++;
        }
        msb = !msb;
    }

    Wire.endTransmission();

    return count;
}

bool I2CDevice::writeBytes(uint8_t regAddr, uint8_t length, uint8_t *data) {
    uint8_t status = 0;

    Wire.beginTransmission(address);
    Wire.write((uint8_t) regAddr);
    Wire.write(data, length);

    status = Wire.endTransmission();

    return status == 0;
}

bool I2CDevice::writeWords(uint8_t regAddr, uint8_t length, uint16_t *data) {
    uint8_t status = 0;

    Wire.beginTransmission(address);
    Wire.write(regAddr);

    for (uint8_t i = 0; i < length * 2; i++) {
        Wire.write((uint8_t)(data[i] >> 8));
        Wire.write((uint8_t)data[i++]);
    }

    status = Wire.endTransmission();

    return status == 0;
}

#endif // defined(ARDUINO) || defined(SPARK)
