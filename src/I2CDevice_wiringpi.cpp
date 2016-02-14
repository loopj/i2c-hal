// Framework-specific I2C methods, for the WiringPi platform

#ifdef RASPBERRYPI

#include <wiringPi.h>

#include "I2CDevice.h"

bool I2CDevice::readBytes(uint8_t regAddr, uint8_t length, uint8_t *data) {
    return true;
}

bool I2CDevice::writeBytes(uint8_t regAddr, uint8_t length, uint8_t *data) {
    return true;
}

void I2CDevice::usleep(unsigned int us) {
    delayMicroseconds(us);
}

#endif // defined(RASPBERRYPI)
