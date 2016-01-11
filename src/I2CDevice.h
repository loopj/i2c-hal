#pragma once

#include <stdint.h>

class I2CDevice {
protected:
    int8_t readWords(uint8_t regAddr, uint8_t length, uint16_t *data);
    int8_t readWord(uint8_t regAddr, uint16_t *data);
    int8_t readBytes(uint8_t regAddr, uint8_t length, uint8_t *data);
    int8_t readByte(uint8_t regAddr, uint8_t *data);
    int8_t readBit(uint8_t regAddr, uint8_t bitNum, uint8_t *data);
    int8_t readBits(uint8_t regAddr, uint8_t bitNum, uint8_t length, uint8_t *data);

    bool writeBytes(uint8_t regAddr, uint8_t length, uint8_t *data);
    bool writeByte(uint8_t regAddr, uint8_t data);
    bool writeBit(uint8_t regAddr, uint8_t bitNum, uint8_t data);

    uint8_t address;
    uint8_t buffer[256];
};
