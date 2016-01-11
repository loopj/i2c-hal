// Particle implmentation
#include "application.h"

#include "I2CDevice.h"

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

int8_t I2CDevice::readWord(uint8_t regAddr, uint16_t *data) {
    return readWords(regAddr, 1, data);
}

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

int8_t I2CDevice::readByte(uint8_t regAddr, uint8_t *data) {
    return readBytes(regAddr, 1, data);
}

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

bool I2CDevice::writeBytes(uint8_t regAddr, uint8_t length, uint8_t *data) {
    uint8_t status = 0;

    Wire.beginTransmission(address);
    Wire.write((uint8_t) regAddr);
    Wire.write(data, length);
    Wire.endTransmission();

    return status == 0;
}

bool I2CDevice::writeByte(uint8_t regAddr, uint8_t data) {
    return writeBytes(regAddr, 1, &data);
}

bool I2CDevice::writeBit(uint8_t regAddr, uint8_t bitNum, uint8_t data) {
    uint8_t b;
    readByte(regAddr, &b);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));

    return writeByte(regAddr, b);
}
