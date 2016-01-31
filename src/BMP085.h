#pragma once

#include "Sensor_Config.h"

#ifdef BMP085_INSTALLED

#include "I2CDevice.h"
#include "Barometer.h"
#include "Thermometer.h"

// Device info
#define BMP085_ADDRESS             0x77
#define BMP085_DEVICE_ID           0x55

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
    BMP085();
    void initialize();
    bool testConnection();

    // Barometer
    float getPressure();

    // Thermometer
    float getTemperature();

    // CAL registers
    void loadCalibration();

    // CHIPID register
    uint8_t getDeviceID();

    // CONTROL register
    uint8_t getControl();
    void setControl(uint8_t value);
    void setOversamplingMode(uint8_t mode);

    // DATA register
    int32_t getRawTemperature();
    int32_t getRawPressure();

protected:
    int16_t  ac1, ac2, ac3;
    uint16_t ac4, ac5, ac6;
    int16_t  b1, b2;
    int16_t  mb, mc, md;

    uint8_t oss = 0;

    int32_t computeB5(int32_t ut);
};

#endif // BMP085_INSTALLED
