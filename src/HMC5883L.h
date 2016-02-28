#pragma once

#include <string.h>

#include "I2CDevice.h"
#include "Magnetometer.h"
#include "Vector3.h"

// Device info
#define HMC5883L_ADDRESS            0x1E
#define HMC5883L_ID                 "H43"

// Register map
enum {
    HMC5883L_RA_CONFIG_A    = 0x00, // R/W
    HMC5883L_RA_CONFIG_B    = 0x01, // R/W
    HMC5883L_RA_MODE        = 0x02, // R/W
    HMC5883L_RA_DATAX_H     = 0x03, // R
    HMC5883L_RA_DATAX_L     = 0x04, // R
    HMC5883L_RA_DATAZ_H     = 0x05, // R
    HMC5883L_RA_DATAZ_L     = 0x06, // R
    HMC5883L_RA_DATAY_H     = 0x07, // R
    HMC5883L_RA_DATAY_L     = 0x08, // R
    HMC5883L_RA_STATUS      = 0x09, // R
    HMC5883L_RA_ID_A        = 0x0A, // R
    HMC5883L_RA_ID_B        = 0x0B, // R
    HMC5883L_RA_ID_C        = 0x0C  // R
};

// CONFIG_A
#define HMC5883L_CONFIG_A_MA_BIT    6
#define HMC5883L_CONFIG_A_MA_LEN    2
#define HMC5883L_CONFIG_A_DO_BIT    4
#define HMC5883L_CONFIG_A_DO_LEN    3
#define HMC5883L_CONFIG_A_MS_BIT    1
#define HMC5883L_CONFIG_A_MS_LEN    2

// CONFIG_A MA
#define HMC5883L_AVERAGE_1          0x00
#define HMC5883L_AVERAGE_2          0x01
#define HMC5883L_AVERAGE_4          0x02
#define HMC5883L_AVERAGE_8          0x03

// CONFIG_A DO
#define HMC5883L_RATE_0P75          0x00
#define HMC5883L_RATE_1P5           0x01
#define HMC5883L_RATE_3             0x02
#define HMC5883L_RATE_7P5           0x03
#define HMC5883L_RATE_15            0x04
#define HMC5883L_RATE_30            0x05
#define HMC5883L_RATE_75            0x06

// CONFIG_A MS
#define HMC5883L_BIAS_NORMAL        0x00
#define HMC5883L_BIAS_POSITIVE      0x01
#define HMC5883L_BIAS_NEGATIVE      0x02

// CONFIG_B
#define HMC5883L_CONFIG_B_GN_BIT    7
#define HMC5883L_CONFIG_B_GN_LEN    3

// CONFIG_B GN
#define HMC5883L_GAIN_1370          0x00
#define HMC5883L_GAIN_1090          0x01
#define HMC5883L_GAIN_820           0x02
#define HMC5883L_GAIN_660           0x03
#define HMC5883L_GAIN_440           0x04
#define HMC5883L_GAIN_390           0x05
#define HMC5883L_GAIN_330           0x06
#define HMC5883L_GAIN_230           0x07

// MODE
#define HMC5883L_MODE_HS_BIT        7
#define HMC5883L_MODE_MD_BIT        1
#define HMC5883L_MODE_MD_LEN        2

// MODE MD
#define HMC5883L_MODE_CONTINUOUS    0x00
#define HMC5883L_MODE_SINGLE        0x01
#define HMC5883L_MODE_IDLE          0x02

// STATUS
#define HMC5883L_STATUS_LOCK_BIT    1
#define HMC5883L_STATUS_RDY_BIT     0

class HMC5883L : public I2CDevice, public Magnetometer {
public:
    static HMC5883L& getInstance() {
        static HMC5883L instance;
        return instance;
    }

    // Initialization
    HMC5883L() : I2CDevice(HMC5883L_ADDRESS) {

    }

    void initialize() {
        setMode(HMC5883L_MODE_CONTINUOUS);
        setDataRate(HMC5883L_RATE_75);

        // Calculate the scale factor from the configured gain
        uint8_t gain = getGain();
        scale = getScale(gain);
    }

    bool testConnection() {
        readBytes(HMC5883L_RA_ID_A, 3, buffer);
        return (strncmp((char *)buffer, HMC5883L_ID, 3) == 0);
    }

    // Magnetometer
    Vector3 getMagneticField() {
        Vector3 magneticField;

        // Read raw measurement data
        int16_t rawField[3];
        getRawMeasurement(rawField);

        // Apply magnetometer scale to get Gauss, convert to microtesla
        magneticField.x = rawField[0]/scale * GAUSS_TO_MICROTESLA;
        magneticField.y = rawField[1]/scale * GAUSS_TO_MICROTESLA;
        magneticField.z = rawField[2]/scale * GAUSS_TO_MICROTESLA;

        return magneticField;
    }

    // CONFIG_A register
    uint8_t getSampleAveraging() {
        readBits(HMC5883L_RA_CONFIG_A, HMC5883L_CONFIG_A_MA_BIT, HMC5883L_CONFIG_A_MA_LEN, buffer);
        return buffer[0];
    }

    void setSampleAveraging(uint8_t averaging) {
        writeBits(HMC5883L_RA_CONFIG_A, HMC5883L_CONFIG_A_MA_BIT, HMC5883L_CONFIG_A_MA_LEN, averaging);
    }

    uint8_t getDataRate() {
        readBits(HMC5883L_RA_CONFIG_A, HMC5883L_CONFIG_A_DO_BIT, HMC5883L_CONFIG_A_DO_LEN, buffer);
        return buffer[0];
    }

    void setDataRate(uint8_t rate) {
        writeBits(HMC5883L_RA_CONFIG_A, HMC5883L_CONFIG_A_DO_BIT, HMC5883L_CONFIG_A_DO_LEN, rate);
    }

    uint8_t getMeasurementBias() {
        readBits(HMC5883L_RA_CONFIG_A, HMC5883L_CONFIG_A_MS_BIT, HMC5883L_CONFIG_A_MS_LEN, buffer);
        return buffer[0];
    }

    void setMeasurementBias(uint8_t bias) {
        writeBits(HMC5883L_RA_CONFIG_A, HMC5883L_CONFIG_A_MS_BIT, HMC5883L_CONFIG_A_MS_LEN, bias);
    }

    // CONFIG_B register
    uint8_t getGain() {
        readBits(HMC5883L_RA_CONFIG_B, HMC5883L_CONFIG_B_GN_BIT, HMC5883L_CONFIG_B_GN_LEN, buffer);
        return buffer[0];
    }

    void setGain(uint8_t gain) {
        writeBits(HMC5883L_RA_CONFIG_A, HMC5883L_CONFIG_B_GN_BIT, HMC5883L_CONFIG_B_GN_LEN, gain);
        scale = getScale(gain);
    }

    // MODE register
    uint8_t getMode() {
        readBits(HMC5883L_RA_MODE, HMC5883L_MODE_MD_BIT, HMC5883L_MODE_MD_LEN, buffer);
        return buffer[0];
    }

    void setMode(uint8_t mode) {
        writeBits(HMC5883L_RA_MODE, HMC5883L_MODE_MD_BIT, HMC5883L_MODE_MD_LEN, mode);
    }

    // DATA registers
    void getRawMeasurement(int16_t *rawField) {
        readBytes(HMC5883L_RA_DATAX_H, 6, buffer);
        rawField[0] = (((int16_t)buffer[0]) << 8) | buffer[1];
        rawField[1] = (((int16_t)buffer[4]) << 8) | buffer[5];
        rawField[2] = (((int16_t)buffer[2]) << 8) | buffer[3];
    }

    // STATUS registers
    bool getLockStatus() {
        readBit(HMC5883L_RA_STATUS, HMC5883L_STATUS_LOCK_BIT, buffer);
        return buffer[0];
    }

    bool getReadyStatus() {
        readBit(HMC5883L_RA_STATUS, HMC5883L_STATUS_RDY_BIT, buffer);
        return buffer[0];
    }

protected:
    float scale;

    float getScale(uint8_t gain) {
        switch(gain) {
            case HMC5883L_GAIN_1370:
                return 1370.0;
            case HMC5883L_GAIN_1090:
                return 1090.0;
            case HMC5883L_GAIN_820:
                return 820.0;
            case HMC5883L_GAIN_660:
                return 660.0;
            case HMC5883L_GAIN_440:
                return 440.0;
            case HMC5883L_GAIN_390:
                return 390.0;
            case HMC5883L_GAIN_330:
                return 330.0;
            case HMC5883L_GAIN_230:
                return 230.0;
            default:
                return 1090.0;
        }
    }
};
