// Framework-specific I2C methods, for ARM mbed platform

#ifdef __MBED__

#include "mbed.h"

#include "I2C.h"

// I2C device handle (internal)
I2C i2c(I2C_SDA, I2C_SCL);

void I2C_init() {
    // Use high-speed i2c
    i2c.frequency(400000);    
}

bool I2C_readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data) {
    // Start the i2c transaction
    i2c.start();

    // Select the slave address and register to read from
    i2c.write(devAddr << 1);
    i2c.write(regAddr);

    // // Read the data
    i2c.read(devAddr << 1, (char *)data, length);

    return true;
}

bool I2C_writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data) {
    // Start the i2c transaction
    i2c.start();

    // Select the slave address and register to write to
    i2c.write(devAddr << 1);
    i2c.write(regAddr);

    // Write the data
    for(int i = 0; i < length; i++) {
        i2c.write(data[i]);
    }

    // Finish the i2c transaction
    i2c.stop();

    return true;
}

void I2C_usleep(unsigned int us) {
    wait_us(us);
}

#endif // defined(__MBED__)
