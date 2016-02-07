// Framework-specific I2C methods, for Arduino and Particle devices

#ifdef __MBED__

#include "mbed.h"

#include "I2CDevice.h"

I2C i2c(I2C_SDA, I2C_SCL);

bool I2CDevice::readBytes(uint8_t regAddr, uint8_t length, uint8_t *data) {
    // Select the slave address and register to read from
    i2c.write(address << 1, (const char *)(&regAddr), 1);

    // Request length bytes of data
    int status = i2c.read(address << 1, (char *)data, length);

    return (status == 0);
}

bool I2CDevice::writeBytes(uint8_t regAddr, uint8_t length, uint8_t *data) {
    // Select the slave address and register to write to
    i2c.write(address << 1, (const char *)(&regAddr), 1);

    // Write the data
    int status = i2c.write(address << 1, (const char *)(data), length);

    return (status == 0);
}

void I2CDevice::usleep(unsigned int us) {
    wait_us(us);
}

#endif // defined(__MBED__)
