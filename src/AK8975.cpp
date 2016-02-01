#include "Sensor_Config.h"

#ifdef AK8975_INSTALLED

#include "AK8975.h"

// Initialization
AK8975::AK8975(uint8_t address) {
    this->address = address;
}

void AK8975::initialize() {
    // Fetch sensitivity adjustment values from the fuse-rom
    setMode(AK8975_MODE_FUSEROM);
    getSensitivityAdjustment(asa);

    // Enable continuous measurement at maximum resolution
    setMode(AK8975_MODE_SINGLE);

    // Calculate the scale factor from the ASA factors
    scale.x = getScale(asa[0]);
    scale.y = getScale(asa[1]);
    scale.z = getScale(asa[2]);
}

bool AK8975::testConnection() {
    return getDeviceID() == AK8975_DEVICE_ID;
}

// Magnetometer
Vector3 AK8975::getMagneticField() {
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
uint8_t AK8975::getDeviceID() {
    readByte(AK8975_RA_WIA, buffer);
    return buffer[0];
}

// ST1 register
bool AK8975::getDataReady() {
    readBit(AK8975_RA_ST1, AK8975_ST1_DRDY_BIT, buffer);
    return buffer[0];
}

// H registers
void AK8975::getRawMeasurement(int16_t *rawField) {
    // Switch to single measurement mode and wait for data
    writeBits(AK8975_RA_CNTL, AK8975_CNTL_MODE_BIT, AK8975_CNTL_MODE_LEN, AK8975_MODE_SINGLE);
    while(!getDataReady()) {
        usleep(100);
    }

    // Read the data
    readBytes(AK8975_RA_HXL, 6, buffer);
    rawField[0] = (((int16_t)buffer[1]) << 8) | buffer[0];
    rawField[1] = (((int16_t)buffer[3]) << 8) | buffer[2];
    rawField[2] = (((int16_t)buffer[5]) << 8) | buffer[4];
}

// ST2 register
bool AK8975::getOverflowStatus() {
    readBit(AK8975_RA_ST2, AK8975_ST2_HOFL_BIT, buffer);
    return buffer[0];
}

bool AK8975::getDataError() {
    readBit(AK8975_RA_ST2, AK8975_ST2_DERR_BIT, buffer);
    return buffer[0];
}

// CNTL register
uint8_t AK8975::getMode() {
    readBits(AK8975_RA_CNTL, AK8975_CNTL_MODE_BIT, AK8975_CNTL_MODE_LEN, buffer);
    return buffer[0];
}

void AK8975::setMode(uint8_t mode) {
    // When user wants to change operation mode, transit to power-down mode
    // first and then transit to other modes. After power-down mode is set, at
    // least 100us(Twat) is needed before setting another mode.
    writeBits(AK8975_RA_CNTL, AK8975_CNTL_MODE_BIT, AK8975_CNTL_MODE_LEN, AK8975_MODE_POWERDOWN);
    usleep(AK8975_TWAT_US);
    writeBits(AK8975_RA_CNTL, AK8975_CNTL_MODE_BIT, AK8975_CNTL_MODE_LEN, mode);
}

// ASA registers
void AK8975::getSensitivityAdjustment(uint8_t *asa) {
    readBytes(AK8975_RA_ASAX, 3, asa);
}

// Private
float AK8975::getScale(uint8_t asa) {
    // Get the scale factor from raw to uT
    float resScale = 1229.0 / 4096.0;

    // Apply sensitivity adjustments according to datasheet
    // Hadj = H * (ASA + 128) / 256
    return ((asa + 128.0) / 256.0) * resScale;
}

#endif // AK8975_INSTALLED
