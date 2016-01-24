#pragma once

#include <stdint.h>

class I2CDevice {
public:
    // Perform any required device initialization
    virtual void initialize() = 0;

    // Confirm that this device is actually connected to the I2C bus
    virtual bool testConnection() = 0;

protected:
    // Read data from the specified I2C register on this device
    int8_t readBit(uint8_t regAddr, uint8_t bitNum, uint8_t *data);
    int8_t readBits(uint8_t regAddr, uint8_t bitNum, uint8_t length, uint8_t *data);
    int8_t readByte(uint8_t regAddr, uint8_t *data);
    int8_t readBytes(uint8_t regAddr, uint8_t length, uint8_t *data);
    int8_t readWord(uint8_t regAddr, uint16_t *data);
    int8_t readWordSigned(uint8_t regAddr, int16_t *data);
    int8_t readWords(uint8_t regAddr, uint8_t length, uint16_t *data);

    // Write data to the specified I2C register on this device
    bool writeBit(uint8_t regAddr, uint8_t bitNum, uint8_t data);
    bool writeBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
    bool writeByte(uint8_t regAddr, uint8_t data);
    bool writeBytes(uint8_t regAddr, uint8_t length, uint8_t *data);
    bool writeWord(uint8_t regAddr, uint16_t data);
    bool writeWords(uint8_t regAddr, uint8_t length, uint16_t *data);

    // Platform-independent sleep/delay
    void usleep(unsigned int us);

    // The I2C address for this device
    uint8_t address;

    // Convenient buffer for read operations
    uint8_t buffer[64];
};
