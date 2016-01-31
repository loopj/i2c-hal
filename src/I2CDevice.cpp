// Framework-independent I2C methods

#include "I2CDevice.h"

int8_t I2CDevice::readBit(uint8_t regAddr, uint8_t bitNum, uint8_t *data) {
    uint8_t b;
    uint8_t count = readByte(regAddr, &b);
    *data = b & (1 << bitNum);

    return count;
}

int8_t I2CDevice::readBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data) {
    uint8_t count, b;
    if ((count = readByte(regAddr, &b)) != 0) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        b &= mask;
        b >>= (bitStart - length + 1);
        *data = b;
    }
    return count;
}

int8_t I2CDevice::readByte(uint8_t regAddr, uint8_t *data) {
    return readBytes(regAddr, 1, data);
}

int8_t I2CDevice::readWord(uint8_t regAddr, uint16_t *data) {
    return readWords(regAddr, 1, data);
}

int8_t I2CDevice::readWordSigned(uint8_t regAddr, int16_t *data) {
    uint16_t temp;

    int8_t status = readWords(regAddr, 1, &temp);
    *data = (int16_t)temp;

    return status;
}

bool I2CDevice::writeBit(uint8_t regAddr, uint8_t bitNum, uint8_t data) {
    uint8_t b;
    readByte(regAddr, &b);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));

    return writeByte(regAddr, b);
}

bool I2CDevice::writeBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) {
    uint8_t b;
    if(readByte(regAddr, &b) != 0) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        data <<= (bitStart - length + 1); // shift data into correct position
        data &= mask; // zero all non-important bits in data
        b &= ~(mask); // zero all important bits in existing byte
        b |= data; // combine data with existing byte

        return writeByte(regAddr, b);
    } else {
        return false;
    }
}

bool I2CDevice::writeByte(uint8_t regAddr, uint8_t data) {
    return writeBytes(regAddr, 1, &data);
}

bool I2CDevice::writeWord(uint8_t regAddr, uint16_t data) {
    return writeWords(regAddr, 1, &data);
}
