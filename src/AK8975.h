#pragma once

#include "Sensor_Config.h"

#ifdef AK8975_INSTALLED

#include "I2CDevice.h"
#include "Magnetometer.h"
#include "Vector3.h"

// Device info
#define AK8975_ADDRESS_00           0x0C
#define AK8975_ADDRESS_01           0x0D
#define AK8975_ADDRESS_10           0x0E
#define AK8975_ADDRESS_11           0x0F
#define AK8975_DEFAULT_ADDRESS      AK8975_ADDRESS_00
#define AK8975_DEVICE_ID            0x48
#define AK8975_TWAT_US              100

// Register map
enum {
    AK8975_RA_WIA       = 0x00, // R
    AK8975_RA_INFO      = 0x01, // R
    AK8975_RA_ST1       = 0x02, // R
    AK8975_RA_HXL       = 0x03, // R
    AK8975_RA_HXH       = 0x04, // R
    AK8975_RA_HYL       = 0x05, // R
    AK8975_RA_HYH       = 0x06, // R
    AK8975_RA_HZL       = 0x07, // R
    AK8975_RA_HZH       = 0x08, // R
    AK8975_RA_ST2       = 0x09, // R
    AK8975_RA_CNTL      = 0x0A, // R/W
    AK8975_RA_RSV       = 0x0B, // R/W - reserved, no not use
    AK8975_RA_ASTC      = 0x0C, // R/W
    AK8975_RA_TS1       = 0x0D, // R/W - test registers for shipment test, do not use
    AK8975_RA_TS2       = 0x0E, // R/W - test registers for shipment test, do not use
    AK8975_RA_I2CDIS    = 0x0F, // R/W
    AK8975_RA_ASAX      = 0x10, // R
    AK8975_RA_ASAY      = 0x11, // R
    AK8975_RA_ASAZ      = 0x12  // R
};

// ST1
#define AK8975_ST1_DRDY_BIT     0

// ST2
#define AK8975_ST2_DERR_BIT     2
#define AK8975_ST2_HOFL_BIT     3

// CNTL
#define AK8975_CNTL_MODE_BIT     3
#define AK8975_CNTL_MODE_LEN     4

// CNTL MODE
#define AK8975_MODE_POWERDOWN           0x0
#define AK8975_MODE_SINGLE              0x1
#define AK8975_MODE_SELFTEST            0x8
#define AK8975_MODE_FUSEROM             0xF

class AK8975 : public I2CDevice, public Magnetometer {
public:
    static AK8975& getInstance() {
        static AK8975 instance;
        return instance;
    }

    // Initialization
    AK8975(uint8_t address = AK8975_DEFAULT_ADDRESS);
    void initialize();
    bool testConnection();

    // Magnetometer
    Vector3 getMagneticField();

    // WIA register
    uint8_t getDeviceID();

    // ST1 register
    bool getDataReady();

    // H registers
    void getRawMeasurement(int16_t *rawField);

    // ST2 register
    bool getOverflowStatus();
    bool getDataError();

    // CNTL register
    uint8_t getMode();
    void setMode(uint8_t mode);

    // ASA registers
    void getSensitivityAdjustment(uint8_t *asa);

protected:
    float getScale(uint8_t asa);
    uint8_t asa[3];
    Vector3 scale;
};

#endif // AK8975_INSTALLED
