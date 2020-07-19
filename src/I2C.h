#pragma once

#include <stdint.h>

// Perform any platform-specific I2C bus initialization
void I2C_init();

// Read data from the specified I2C register on this device
bool I2C_readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data);
bool I2C_readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t length, uint8_t *data);
bool I2C_readWordBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data);
bool I2C_readWordBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t length, uint16_t *data);
bool I2C_readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data);
bool I2C_readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);
bool I2C_readWord(uint8_t devAddr, uint8_t regAddr, uint16_t *data);
bool I2C_readWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data);

// Write data to the specified I2C register on this device
bool I2C_writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data);
bool I2C_writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
bool I2C_writeWordBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data);
bool I2C_writeWordBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t data);
bool I2C_writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data);
bool I2C_writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);
bool I2C_writeWord(uint8_t devAddr, uint16_t regAddr, uint16_t data);

// Platform-independent sleep/delay
void I2C_usleep(unsigned int us);