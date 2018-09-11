// Framework-independent I2C methods

#include "I2CDevice.h"

bool I2CDevice::readBit(uint8_t regAddr, uint8_t bitNum, uint8_t *data) {
    uint8_t b;
    bool status = readByte(regAddr, &b);
    *data = b & (1 << bitNum);

    return status;
}

bool I2CDevice::readBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data) {
    bool status = false;
    uint8_t b;
    if ((status = readByte(regAddr, &b))) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        b &= mask;
        b >>= (bitStart - length + 1);
        *data = b;
    }
    return status;
}

bool I2CDevice::readWordBit(uint8_t regAddr, uint8_t bitNum, uint8_t *data) {
    uint16_t b;
    bool status = readWord(regAddr, &b);
    *data = (uint8_t) (b & (1 << bitNum));

    return status;
}

bool I2CDevice::readWordBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t *data) {
    bool status = false;
    uint16_t b;
    if ((status = readWord(regAddr, &b))) {
        uint16_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        b &= mask;
        b >>= (bitStart - length + 1);
        *data = b;
    }
    return status;
}

bool I2CDevice::readByte(uint8_t regAddr, uint8_t *data) {
    return readBytes(regAddr, 1, data);
}

bool I2CDevice::readWord(uint8_t regAddr, uint16_t *data) {
    return readWords(regAddr, 1, data);
}

bool I2CDevice::readWords(uint8_t regAddr, uint8_t length, uint16_t *data) {
    uint8_t temp[length*2];
    bool status = readBytes(regAddr, length*2, temp);

    for(int i=0; i<length; i++) {
        data[i] = (temp[i*2] << 8) | temp[i*2 + 1];
    }

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

bool I2CDevice::writeWordBit(uint8_t regAddr, uint8_t bitNum, uint8_t data) {
    uint16_t b;
    readWord(regAddr, &b);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));

    return writeWord(regAddr, b);
}

bool I2CDevice::writeWordBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t data) {
    uint16_t b;
    if(readWord(regAddr, &b) != 0) {
        uint16_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        data <<= (bitStart - length + 1); // shift data into correct position
        data &= mask; // zero all non-important bits in data
        b &= ~(mask); // zero all important bits in existing byte
        b |= data; // combine data with existing byte

        return writeWord(regAddr, b);
    } else {
        return false;
    }
}

bool I2CDevice::writeByte(uint8_t regAddr, uint8_t data) {
    return writeBytes(regAddr, 1, &data);
}

bool I2CDevice::writeWord(uint16_t regAddr, uint16_t data) {
    return writeBytes(regAddr, 2, (uint8_t *)&data);
}
