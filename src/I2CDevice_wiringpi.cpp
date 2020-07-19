// Framework-specific I2C methods, for the WiringPi platform

#ifdef RASPBERRYPI

#include <fcntl.h>
#include <linux/i2c-dev.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "I2C.h"

int handle;

void I2C_init(uint8_t address) {
    handle = wiringPiI2CSetup(address);
}

bool I2C_readBytes(uint8_t regAddr, uint8_t length, uint8_t *data) {
    uint8_t count = i2c_smbus_read_i2c_block_data(handle, regAddr, length, data);

    return (count == length);
}

bool I2C_writeBytes(uint8_t regAddr, uint8_t length, uint8_t *data) {
    uint8_t count = i2c_smbus_write_i2c_block_data(handle, regAddr, length, data);

    return (count == length);
}

void I2C_usleep(unsigned int us) {
    delayMicroseconds(us);
}

#endif // defined(RASPBERRYPI)
