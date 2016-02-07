#include "mbed.h"
#include "USBSerial.h"

I2C i2c(I2C_SDA, I2C_SCL);
USBSerial serial;

char readByte(uint8_t address, uint8_t subAddress) {
    char data[1]; // `data` will store the register data
    char data_write[1];
    data_write[0] = subAddress;
    i2c.write(address, data_write, 1, 1); // no stop
    i2c.read(address, data, 1, 0);
    return data[0];
}

int main() {
    wait_ms(5000);

    while(1) {
        uint8_t raxh = readByte(0x68, 0x13);
        uint8_t raxl = readByte(0x68, 0x14);

        int16_t rawAccel = (int16_t)(((int16_t)raxh << 8) | raxl);

        serial.printf("rax: %d\n", rawAccel);

        wait_ms(50);
    }
}
