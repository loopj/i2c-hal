// Framework-specific I2C methods, for Arduino and Particle devices

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

    // Select the slave address and register to read from
    Wire.beginTransmission(address);
    Wire.write(regAddr);
    Wire.endTransmission();

    // Request length bytes of data
    Wire.requestFrom(address, length);
    while(Wire.available()) {
        data[count] = Wire.read();
        count++;
    }

    return count;
}

int8_t I2CDevice::readWords(uint8_t regAddr, uint8_t length, uint16_t *data) {
    uint8_t count = 0;

    // Select the slave address and register to read from
    Wire.beginTransmission(address);
    Wire.write(regAddr);
    Wire.endTransmission();

    // Request length*2 bytes of data
    Wire.requestFrom(address, (uint8_t)(length * 2));
    bool msb = true;
    while(Wire.available()) {
        // Combine bytes into words
        if (msb) {
            data[count] = Wire.read() << 8;
        } else {
            data[count] |= Wire.read();
            count++;
        }
        msb = !msb;
    }

    return count;
}

bool I2CDevice::writeBytes(uint8_t regAddr, uint8_t length, uint8_t *data) {
    // Select the slave address and register to write to
    Wire.beginTransmission(address);
    Wire.write(regAddr);

    // Write the data
    Wire.write(data, length);

    // Finish transmission and return the status
    return (Wire.endTransmission() == 0);
}

bool I2CDevice::writeWords(uint8_t regAddr, uint8_t length, uint16_t *data) {
    // Select the slave address and register to write to
    Wire.beginTransmission(address);
    Wire.write(regAddr);

    // Write the data
    for (uint8_t i = 0; i < length * 2; i++) {
        Wire.write((uint8_t)(data[i] >> 8));
        Wire.write((uint8_t)data[i++]);
    }

    // Finish transmission and return the status
    return (Wire.endTransmission() == 0);
}

void I2CDevice::usleep(unsigned int us) {
    delayMicroseconds(us);
}

#endif // defined(ARDUINO) || defined(SPARK)
