#pragma once

#include "Sensor_Config.h"

#ifdef AK8963_INSTALLED

#include "I2CDevice.h"
#include "Magnetometer.h"
#include "Vector3.h"

// Device info
#define AK8963_ADDRESS_00           0x0C
#define AK8963_ADDRESS_01           0x0D
#define AK8963_ADDRESS_10           0x0E
#define AK8963_ADDRESS_11           0x0F
#define AK8963_DEFAULT_ADDRESS      AK8963_ADDRESS_00
#define AK8963_DEVICE_ID            0x48
#define AK8963_TWAT_US              100

// Register map
enum {
    AK8963_RA_WIA       = 0x00, // R
    AK8963_RA_INFO      = 0x01, // R
    AK8963_RA_ST1       = 0x02, // R
    AK8963_RA_HXL       = 0x03, // R
    AK8963_RA_HXH       = 0x04, // R
    AK8963_RA_HYL       = 0x05, // R
    AK8963_RA_HYH       = 0x06, // R
    AK8963_RA_HZL       = 0x07, // R
    AK8963_RA_HZH       = 0x08, // R
    AK8963_RA_ST2       = 0x09, // R
    AK8963_RA_CNTL1     = 0x0A, // R/W
    AK8963_RA_CNTL2     = 0x0B, // R/W
    AK8963_RA_ASTC      = 0x0C, // R/W
    AK8963_RA_TS1       = 0x0D, // R/W - test registers for shipment test, do not use
    AK8963_RA_TS2       = 0x0E, // R/W - test registers for shipment test, do not use
    AK8963_RA_I2CDIS    = 0x0F, // R/W
    AK8963_RA_ASAX      = 0x10, // R
    AK8963_RA_ASAY      = 0x11, // R
    AK8963_RA_ASAZ      = 0x12  // R
};

// ST1
#define AK8963_ST1_DRDY_BIT     0
#define AK8963_ST1_DOR_BIT      1

// ST2
#define AK8963_ST2_HOFL_BIT     3
#define AK8963_ST2_BITM_BIT     4

// CNTL1
#define AK8963_CNTL1_MODE_BIT     3
#define AK8963_CNTL1_MODE_LEN     4
#define AK8963_CNTL1_BIT_BIT      4

// CNTL1 MODE
#define AK8963_MODE_POWERDOWN           0x0
#define AK8963_MODE_SINGLE              0x1
#define AK8963_MODE_CONTINUOUS_8HZ      0x2
#define AK8963_MODE_EXTERNAL            0x4
#define AK8963_MODE_CONTINUOUS_100HZ    0x6
#define AK8963_MODE_SELFTEST            0x8
#define AK8963_MODE_FUSEROM             0xF

// CNTL1 BIT (resolution)
#define AK8963_BIT_14                   0
#define AK8963_BIT_16                   1

// CNTL2
#define AK8963_CNTL2_SRST               0x01

class AK8963 : public I2CDevice, public Magnetometer {
public:
    static AK8963& getInstance() {
        static AK8963 instance;
        return instance;
    }

    // Initialization
    AK8963(uint8_t address = AK8963_DEFAULT_ADDRESS);
    void initialize();
    bool testConnection();

    // Magnetometer
    Vector3 getMagneticField();

    // WIA register
    uint8_t getDeviceID();

    // ST1 register
    bool getDataReady();
    bool getDataOverrun();

    // H registers
    void getRawMeasurement(int16_t *rawField);

    // ST2 register
    bool getOverflowStatus();
    bool getOutputBit();

    // CNTL1 register
    uint8_t getMode();
    void setMode(uint8_t mode);
    uint8_t getResolution();
    void setResolution(uint8_t resolution);

    // CNTL2 register
    void reset();

    // ASA registers
    void getSensitivityAdjustment(uint8_t *asa);

protected:
    float getScale(uint8_t asa, uint8_t resolution);
    uint8_t asa[3];
    Vector3 scale;
};

#endif // AK8963_INSTALLED
