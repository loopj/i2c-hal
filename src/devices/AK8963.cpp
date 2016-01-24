#include "config.h"

#ifdef AK8963_INSTALLED

#include "AK8963.h"

// Initialization
AK8963::AK8963(uint8_t address) {
    this->address = address;
}

void AK8963::initialize() {
    // Fetch sensitivity adjustment values from the fuse-rom
    setMode(AK8963_MODE_FUSEROM);
    sensitivity = getSensitivityAdjustment();

    // Enable continuous measurement at maximum resolution
    setMode(AK8963_MODE_CONTINUOUS_100HZ);
    setResolution(AK8963_BIT_16);

    // Calculate the scale factor from the configured resolution
    uint8_t gain = getResolution();
    scale = getScale(gain);
}

bool AK8963::testConnection() {
    return getDeviceID() == AK8963_DEVICE_ID;
}

// Magnetometer
Vector3 AK8963::getMagneticField() {
    Vector3 magneticField;

    // Read raw measurement data
    int16_t rawField[3];
    getRawMeasurement(rawField);

    // Apply sensitivity adjustments, scale to get uT
    magneticField.x = rawField[0] * sensitivity.x * scale;
    magneticField.y = rawField[1] * sensitivity.y * scale;
    magneticField.z = rawField[2] * sensitivity.z * scale;

    return magneticField;
}

// WIA register
uint8_t AK8963::getDeviceID() {
    readByte(AK8963_RA_WIA, buffer);
    return buffer[0];
}

// ST1 register
bool AK8963::getDataReady() {
    readBit(AK8963_RA_ST1, AK8963_ST1_DRDY_BIT, buffer);
    return buffer[0];
}

bool AK8963::getDataOverrun() {
    readBit(AK8963_RA_ST1, AK8963_ST1_DOR_BIT, buffer);
    return buffer[0];
}

// H registers
void AK8963::getRawMeasurement(int16_t *rawField) {
    // Read data and mark data reading as finished by also reading the ST2 register
    readBytes(AK8963_RA_HXL, 7, buffer);
    rawField[0] = (((int16_t)buffer[1]) << 8) | buffer[0];
    rawField[1] = (((int16_t)buffer[3]) << 8) | buffer[2];
    rawField[2] = (((int16_t)buffer[5]) << 8) | buffer[4];
}

// ST2 register
bool AK8963::getOverflowStatus() {
    readBit(AK8963_RA_ST2, AK8963_ST2_HOFL_BIT, buffer);
    return buffer[0];
}

bool AK8963::getOutputBit() {
    readBit(AK8963_RA_ST2, AK8963_ST2_BITM_BIT, buffer);
    return buffer[0];
}

// CNTL1 register
uint8_t AK8963::getMode() {
    readBits(AK8963_RA_CNTL1, AK8963_CNTL1_MODE_BIT, AK8963_CNTL1_MODE_LEN, buffer);
    return buffer[0];
}

void AK8963::setMode(uint8_t mode) {
    // When user wants to change operation mode, transit to power-down mode
    // first and then transit to other modes. After power-down mode is set, at
    // least 100us(Twat) is needed before setting another mode.
    writeBits(AK8963_RA_CNTL1, AK8963_CNTL1_MODE_BIT, AK8963_CNTL1_MODE_LEN, AK8963_MODE_POWERDOWN);
    usleep(AK8963_TWAT_US);
    writeBits(AK8963_RA_CNTL1, AK8963_CNTL1_MODE_BIT, AK8963_CNTL1_MODE_LEN, mode);
}

uint8_t AK8963::getResolution() {
    readBit(AK8963_RA_CNTL1, AK8963_CNTL1_BIT_BIT, buffer);
    return buffer[0];
}

void AK8963::setResolution(uint8_t resolution) {
    writeBit(AK8963_RA_CNTL1, AK8963_CNTL1_BIT_BIT, resolution);
    scale = getScale(resolution);
}

// CNTL2 register
void AK8963::reset() {
    writeByte(AK8963_RA_CNTL2, AK8963_CNTL2_SRST);
}

// ASA registers
Vector3 AK8963::getSensitivityAdjustment() {
    Vector3 sensitivity;

    readBytes(AK8963_RA_ASAX, 3, &buffer[0]);

    sensitivity.x = (float)(buffer[0] - 128)/256.0 + 1.0;
    sensitivity.y = (float)(buffer[1] - 128)/256.0 + 1.0;
    sensitivity.z = (float)(buffer[2] - 128)/256.0 + 1.0;

    return sensitivity;
}

// Private
float AK8963::getScale(uint8_t resolution) {
    switch(resolution) {
        case AK8963_BIT_14:
            return 4912.0 / 8190.0;
        case AK8963_BIT_16:
            return 4912.0 / 32760.0;
        default:
            return 4912.0 / 32760.0;
    }
}

#endif // AK8963_INSTALLED
