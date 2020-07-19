// Framework-independent I2C methods

#include "I2C.h"

bool I2C_readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data) {
    uint8_t b;
    bool status = I2C_readByte(devAddr, regAddr, &b);
    *data = b & (1 << bitNum);

    return status;
}

bool I2C_readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data) {
    bool status = false;
    uint8_t b;
    if ((status = I2C_readByte(devAddr, regAddr, &b))) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        b &= mask;
        b >>= (bitStart - length + 1);
        *data = b;
    }
    return status;
}

bool I2C_readWordBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data) {
    uint16_t b;
    bool status = I2C_readWord(devAddr, regAddr, &b);
    *data = (uint8_t) (b & (1 << bitNum));

    return status;
}

bool I2C_readWordBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t *data) {
    bool status = false;
    uint16_t b;
    if ((status = I2C_readWord(devAddr, regAddr, &b))) {
        uint16_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        b &= mask;
        b >>= (bitStart - length + 1);
        *data = b;
    }
    return status;
}

bool I2C_readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data) {
    return I2C_readBytes(devAddr, regAddr, 1, data);
}

bool I2C_readWord(uint8_t devAddr, uint8_t regAddr, uint16_t *data) {
    return I2C_readWords(devAddr, regAddr, 1, data);
}

bool I2C_readWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data) {
    uint8_t temp[length*2];
    bool status = I2C_readBytes(devAddr, regAddr, length*2, temp);

    for(int i=0; i<length; i++) {
        data[i] = (temp[i*2] << 8) | temp[i*2 + 1];
    }

    return status;
}

bool I2C_writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data) {
    uint8_t b;
    I2C_readByte(devAddr, regAddr, &b);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));

    return I2C_writeByte(devAddr, regAddr, b);
}

bool I2C_writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) {
    uint8_t b;
    if(I2C_readByte(devAddr, regAddr, &b) != 0) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        data <<= (bitStart - length + 1); // shift data into correct position
        data &= mask; // zero all non-important bits in data
        b &= ~(mask); // zero all important bits in existing byte
        b |= data; // combine data with existing byte

        return I2C_writeByte(devAddr, regAddr, b);
    } else {
        return false;
    }
}

bool I2C_writeWordBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data) {
    uint16_t b;
    I2C_readWord(devAddr, regAddr, &b);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));

    return I2C_writeWord(devAddr, regAddr, b);
}

bool I2C_writeWordBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t data) {
    uint16_t b;
    if(I2C_readWord(devAddr, regAddr, &b) != 0) {
        uint16_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        data <<= (bitStart - length + 1); // shift data into correct position
        data &= mask; // zero all non-important bits in data
        b &= ~(mask); // zero all important bits in existing byte
        b |= data; // combine data with existing byte

        return I2C_writeWord(devAddr, regAddr, b);
    } else {
        return false;
    }
}

bool I2C_writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data) {
    return I2C_writeBytes(devAddr, regAddr, 1, &data);
}

bool I2C_writeWord(uint8_t devAddr, uint16_t regAddr, uint16_t data) {
    return I2C_writeBytes(devAddr, regAddr, 2, (uint8_t *)&data);
}
