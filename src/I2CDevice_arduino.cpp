// Framework-specific I2C methods, for the Arduino and Particle platforms

#if defined(ARDUINO) || defined(SPARK)

#ifdef ARDUINO
    #include "Arduino.h"
    #include <Wire.h>
#endif

#ifdef SPARK
    #include "application.h"
#endif

#include "I2C.h"

void I2C_init() {}

bool I2C_readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data) {
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

    return (count == length);
}

bool I2C_writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data) {
    // Select the slave address and register to write to
    Wire.beginTransmission(address);
    Wire.write(regAddr);

    // Write the data
    Wire.write(data, length);

    // Finish transmission and return the status
    return (Wire.endTransmission() == 0);
}

void I2C_usleep(unsigned int us) {
    delayMicroseconds(us);
}

#endif // defined(ARDUINO) || defined(SPARK)
