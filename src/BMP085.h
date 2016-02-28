#pragma once

#include "I2CDevice.h"
#include "Barometer.h"
#include "Thermometer.h"

// Device info
#define BMP085_ADDRESS             0x77

// Device IDs for CHIPID register
#define BMP085_DEVICE_ID           0x55
#define BMP180_DEVICE_ID           0x55

// Register map
enum {
    BMP085_RA_CAL_AC1            = 0xAA, // R
    BMP085_RA_CAL_AC2            = 0xAC, // R
    BMP085_RA_CAL_AC3            = 0xAE, // R
    BMP085_RA_CAL_AC4            = 0xB0, // R
    BMP085_RA_CAL_AC5            = 0xB2, // R
    BMP085_RA_CAL_AC6            = 0xB4, // R
    BMP085_RA_CAL_B1             = 0xB6, // R
    BMP085_RA_CAL_B2             = 0xB8, // R
    BMP085_RA_CAL_MB             = 0xBA, // R
    BMP085_RA_CAL_MC             = 0xBC, // R
    BMP085_RA_CAL_MD             = 0xBE, // R
    BMP085_RA_CHIPID             = 0xD0, // R
    BMP085_RA_VERSION            = 0xD1, // R
    BMP085_RA_SOFTRESET          = 0xE0, // R/W
    BMP085_RA_CONTROL            = 0xF4, // R/W
    BMP085_RA_DATA               = 0xF6  // R
};

// CONTROL
#define BMP085_CONTROL_TEMPERATURE      0x2E
#define BMP085_CONTROL_PRESSURE         0x34

// CONTROL oversampling modes
#define BMP085_MODE_ULTRALOWPOWER       0
#define BMP085_MODE_STANDARD            1
#define BMP085_MODE_HIGHRES             2
#define BMP085_MODE_ULTRAHIGHRES        3

class BMP085 : public I2CDevice, public Barometer, public Thermometer {
public:
    static BMP085& getInstance() {
        static BMP085 instance;
        return instance;
    }

    // Initialization
    BMP085() : I2CDevice(BMP085_ADDRESS), oss(0) {

    }

    void initialize() {
        loadCalibration();
        setOversamplingMode(BMP085_MODE_STANDARD);
    }

    bool testConnection() {
        return getDeviceID() == BMP085_DEVICE_ID;
    }

    // Barometer
    float getPressure() {
        int32_t ut = getRawTemperature();
        int32_t up = getRawPressure();

        // Calculate true pressure, according to datasheet rules
        int32_t b5 = computeB5(ut);
        int32_t b6 = b5 - 4000;
        int32_t x1 = (b2 * ((b6 * b6) >> 12)) >> 11;
        int32_t x2 = (ac2 * b6) >> 11;
        int32_t x3 = x1 + x2;
        int32_t b3 = (((((int32_t) ac1) * 4 + x3) << oss) + 2) >> 2;
        x1 = (ac3 * b6) >> 13;
        x2 = (b1 * ((b6 * b6) >> 12)) >> 16;
        x3 = ((x1 + x2) + 2) >> 2;
        uint32_t b4 = (ac4 * (uint32_t) (x3 + 32768)) >> 15;
        uint32_t b7 = ((uint32_t) (up - b3) * (50000 >> oss));

        int32_t p;
        if (b7 < 0x80000000) {
            p = (b7 << 1) / b4;
        } else {
            p = (b7 / b4) << 1;
        }

        x1 = (p >> 8) * (p >> 8);
        x1 = (x1 * 3038) >> 16;
        x2 = (-7357 * p) >> 16;

        p = p + ((x1 + x2 + 3791) >> 4);

        // Convert to hPa
        return p / 100.0;
    }

    // Thermometer
    float getTemperature() {
        int16_t ut = getRawTemperature();

        // Calculate true temperature, according to datasheet rules
        int32_t b5 = computeB5(ut);
        float t = (b5+8) >> 4;

        // Convert to C
        return t / 10.0;
    }

    // CAL registers
    void loadCalibration() {
        readWord(BMP085_RA_CAL_AC1, (uint16_t *)(&ac1));
        readWord(BMP085_RA_CAL_AC2, (uint16_t *)(&ac2));
        readWord(BMP085_RA_CAL_AC3, (uint16_t *)(&ac3));
        readWord(BMP085_RA_CAL_AC4, &ac4);
        readWord(BMP085_RA_CAL_AC5, &ac5);
        readWord(BMP085_RA_CAL_AC6, &ac6);
        readWord(BMP085_RA_CAL_B1, (uint16_t *)(&b1));
        readWord(BMP085_RA_CAL_B2, (uint16_t *)(&b2));
        readWord(BMP085_RA_CAL_MB, (uint16_t *)(&mb));
        readWord(BMP085_RA_CAL_MC, (uint16_t *)(&mc));
        readWord(BMP085_RA_CAL_MD, (uint16_t *)(&md));
    }

    // CHIPID register
    uint8_t getDeviceID() {
        readByte(BMP085_RA_CHIPID, buffer);
        return buffer[0];
    }

    // CONTROL register
    uint8_t getControl() {
        readByte(BMP085_RA_CONTROL, buffer);
        return buffer[0];
    }

    void setControl(uint8_t value) {
        writeByte(BMP085_RA_CONTROL, value);
    }

    void setOversamplingMode(uint8_t mode) {
        oss = mode;
    }

    // DATA register
    int32_t getRawTemperature() {
        int16_t rawTemperature;

        // Start temperature measurement
        setControl(BMP085_CONTROL_TEMPERATURE);

        // Wait for the conversion to complete
        usleep(4500);

        // Read the raw temperature data;
        readWord(BMP085_RA_DATA, (uint16_t *)(&rawTemperature));

        return rawTemperature;
    }

    int32_t getRawPressure() {
        int32_t rawPressure;

        // Start pressure measurement, with the configured oversampling setting
        setControl(BMP085_CONTROL_PRESSURE + (oss << 6));

        // Wait for the conversion to complete
        switch(oss) {
            case BMP085_MODE_ULTRALOWPOWER:
                usleep(4500);
                break;
            case BMP085_MODE_STANDARD:
                usleep(7500);
                break;
            case BMP085_MODE_HIGHRES:
                usleep(13500);
                break;
            case BMP085_MODE_ULTRAHIGHRES:
                usleep(25500);
                break;
        }

        // Read the raw pressure data
        readBytes(BMP085_RA_DATA, 3, buffer);
        rawPressure = (((uint32_t)buffer[0] << 16) + ((uint16_t)buffer[1] << 8) + buffer[2]) >> (8 - oss);

        return rawPressure;
    }

protected:
    int16_t  ac1, ac2, ac3;
    uint16_t ac4, ac5, ac6;
    int16_t  b1, b2;
    int16_t  mb, mc, md;

    uint8_t oss;

    int32_t computeB5(int32_t ut) {
        int32_t x1 = (ut - (int32_t)ac6) * ((int32_t)ac5) >> 15;
        int32_t x2 = ((int32_t)mc << 11) / (x1+(int32_t)md);
        return x1 + x2;
    }
};
