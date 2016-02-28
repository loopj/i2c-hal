#pragma once

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
    AK8963(uint8_t address = AK8963_DEFAULT_ADDRESS) : I2CDevice(address) {

    }

    void initialize() {
        // Fetch sensitivity adjustment values from the fuse-rom
        setMode(AK8963_MODE_FUSEROM);
        getSensitivityAdjustment(asa);

        // Enable continuous measurement at maximum resolution
        setMode(AK8963_MODE_CONTINUOUS_100HZ);
        setResolution(AK8963_BIT_16);

        // Calculate the scale factor from the configured resolution
        uint8_t resolution = getResolution();
        scale.x = getScale(asa[0], resolution);
        scale.y = getScale(asa[1], resolution);
        scale.z = getScale(asa[2], resolution);
    }

    bool testConnection() {
        return getDeviceID() == AK8963_DEVICE_ID;
    }

    // Magnetometer
    Vector3 getMagneticField() {
        Vector3 magneticField;

        // Read raw measurement data
        int16_t rawField[3];
        getRawMeasurement(rawField);

        // Apply sensitivity adjustments, scale to get uT
        magneticField.x = rawField[0] * scale.x;
        magneticField.y = rawField[1] * scale.y;
        magneticField.z = rawField[2] * scale.z;

        return magneticField;
    }

    // WIA register
    uint8_t getDeviceID() {
        readByte(AK8963_RA_WIA, buffer);
        return buffer[0];
    }

    // ST1 register
    bool getDataReady() {
        readBit(AK8963_RA_ST1, AK8963_ST1_DRDY_BIT, buffer);
        return buffer[0];
    }

    bool getDataOverrun() {
        readBit(AK8963_RA_ST1, AK8963_ST1_DOR_BIT, buffer);
        return buffer[0];
    }

    // H registers
    void getRawMeasurement(int16_t *rawField) {
        // Read data and mark data reading as finished by also reading the ST2 register
        readBytes(AK8963_RA_HXL, 7, buffer);
        rawField[0] = (((int16_t)buffer[1]) << 8) | buffer[0];
        rawField[1] = (((int16_t)buffer[3]) << 8) | buffer[2];
        rawField[2] = (((int16_t)buffer[5]) << 8) | buffer[4];
    }

    // ST2 register
    bool getOverflowStatus() {
        readBit(AK8963_RA_ST2, AK8963_ST2_HOFL_BIT, buffer);
        return buffer[0];
    }

    bool getOutputBit() {
        readBit(AK8963_RA_ST2, AK8963_ST2_BITM_BIT, buffer);
        return buffer[0];
    }

    // CNTL1 register
    uint8_t getMode() {
        readBits(AK8963_RA_CNTL1, AK8963_CNTL1_MODE_BIT, AK8963_CNTL1_MODE_LEN, buffer);
        return buffer[0];
    }

    void setMode(uint8_t mode) {
        // When user wants to change operation mode, transit to power-down mode
        // first and then transit to other modes. After power-down mode is set, at
        // least 100us(Twat) is needed before setting another mode.
        writeBits(AK8963_RA_CNTL1, AK8963_CNTL1_MODE_BIT, AK8963_CNTL1_MODE_LEN, AK8963_MODE_POWERDOWN);
        usleep(AK8963_TWAT_US);
        writeBits(AK8963_RA_CNTL1, AK8963_CNTL1_MODE_BIT, AK8963_CNTL1_MODE_LEN, mode);
    }

    uint8_t getResolution() {
        readBit(AK8963_RA_CNTL1, AK8963_CNTL1_BIT_BIT, buffer);
        return buffer[0];
    }

    void setResolution(uint8_t resolution) {
        writeBit(AK8963_RA_CNTL1, AK8963_CNTL1_BIT_BIT, resolution);
        scale.x = getScale(asa[0], resolution);
        scale.y = getScale(asa[1], resolution);
        scale.z = getScale(asa[2], resolution);
    }

    // CNTL2 register
    void reset() {
        writeByte(AK8963_RA_CNTL2, AK8963_CNTL2_SRST);
    }

    // ASA registers
    void getSensitivityAdjustment(uint8_t *asa) {
        readBytes(AK8963_RA_ASAX, 3, asa);
    }

protected:
    uint8_t asa[3];
    Vector3 scale;

    float getScale(uint8_t asa, uint8_t resolution) {
        // Get the scale factor from raw to uT, depending on resolution
        float resScale;
        if(resolution == AK8963_BIT_16) {
            resScale = 4912.0 / 32760.0;
        } else {
            resScale = 4912.0 / 8190.0;
        }

        // Apply sensitivity adjustments according to datasheet
        // Hadj = H * (ASA + 128) / 256
        return ((asa + 128.0) / 256.0) * resScale;
    }
};
