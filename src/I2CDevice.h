#pragma once

#include <stdint.h>

class I2CDevice {
public:
    // Constructor
    I2CDevice(uint8_t address);

    // Perform any required device initialization
    virtual void initialize() = 0;

    // Confirm that this device is actually connected to the I2C bus
    virtual bool testConnection() = 0;

protected:
    // Read data from the specified I2C register on this device
    bool readBit(uint8_t regAddr, uint8_t bitNum, uint8_t *data);
    bool readBits(uint8_t regAddr, uint8_t bitNum, uint8_t length, uint8_t *data);
    bool readWordBit(uint8_t regAddr, uint8_t bitNum, uint8_t *data);
    bool readWordBits(uint8_t regAddr, uint8_t bitNum, uint8_t length, uint16_t *data);
    bool readByte(uint8_t regAddr, uint8_t *data);
    bool readBytes(uint8_t regAddr, uint8_t length, uint8_t *data);
    bool readWord(uint8_t regAddr, uint16_t *data);
    bool readWords(uint8_t regAddr, uint8_t length, uint16_t *data);

    // Write data to the specified I2C register on this device
    bool writeBit(uint8_t regAddr, uint8_t bitNum, uint8_t data);
    bool writeBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
    bool writeWordBit(uint8_t regAddr, uint8_t bitNum, uint8_t data);
    bool writeWordBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t data);
    bool writeByte(uint8_t regAddr, uint8_t data);
    bool writeBytes(uint8_t regAddr, uint8_t length, uint8_t *data);
    bool writeWord(uint16_t regAddr, uint16_t data);

    // Platform-independent sleep/delay
    void usleep(unsigned int us);

    // The I2C address for this device
    uint8_t address;

    // Convenient buffer for read operations
    uint8_t buffer[64];

    // I2C device handle (internal)
    int handle;
};
