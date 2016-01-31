#include "Sensor_Config.h"

#ifdef HMC5883L_INSTALLED

#include <string.h>
#include "HMC5883L.h"

// Initialization
HMC5883L::HMC5883L() {
    this->address = HMC5883L_ADDRESS;
}

void HMC5883L::initialize() {
    setMode(HMC5883L_MODE_CONTINUOUS);
    setDataRate(HMC5883L_RATE_75);

    // Calculate the scale factor from the configured gain
    uint8_t gain = getGain();
    scale = getScale(gain);
}

bool HMC5883L::testConnection() {
    readBytes(HMC5883L_RA_ID_A, 3, buffer);
    return (strncmp((char *)buffer, HMC5883L_ID, 3) == 0);
}

// Magnetometer
Vector3 HMC5883L::getMagneticField() {
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
uint8_t HMC5883L::getSampleAveraging() {
    readBits(HMC5883L_RA_CONFIG_A, HMC5883L_CONFIG_A_MA_BIT, HMC5883L_CONFIG_A_MA_LEN, buffer);
    return buffer[0];
}

void HMC5883L::setSampleAveraging(uint8_t averaging) {
    writeBits(HMC5883L_RA_CONFIG_A, HMC5883L_CONFIG_A_MA_BIT, HMC5883L_CONFIG_A_MA_LEN, averaging);
}

uint8_t HMC5883L::getDataRate() {
    readBits(HMC5883L_RA_CONFIG_A, HMC5883L_CONFIG_A_DO_BIT, HMC5883L_CONFIG_A_DO_LEN, buffer);
    return buffer[0];
}

void HMC5883L::setDataRate(uint8_t rate) {
    writeBits(HMC5883L_RA_CONFIG_A, HMC5883L_CONFIG_A_DO_BIT, HMC5883L_CONFIG_A_DO_LEN, rate);
}

uint8_t HMC5883L::getMeasurementBias() {
    readBits(HMC5883L_RA_CONFIG_A, HMC5883L_CONFIG_A_MS_BIT, HMC5883L_CONFIG_A_MS_LEN, buffer);
    return buffer[0];
}

void HMC5883L::setMeasurementBias(uint8_t bias) {
    writeBits(HMC5883L_RA_CONFIG_A, HMC5883L_CONFIG_A_MS_BIT, HMC5883L_CONFIG_A_MS_LEN, bias);
}

// CONFIG_B register
uint8_t HMC5883L::getGain() {
    readBits(HMC5883L_RA_CONFIG_B, HMC5883L_CONFIG_B_GN_BIT, HMC5883L_CONFIG_B_GN_LEN, buffer);
    return buffer[0];
}

void HMC5883L::setGain(uint8_t gain) {
    writeBits(HMC5883L_RA_CONFIG_A, HMC5883L_CONFIG_B_GN_BIT, HMC5883L_CONFIG_B_GN_LEN, gain);
    scale = getScale(gain);
}

// MODE register
uint8_t HMC5883L::getMode() {
    readBits(HMC5883L_RA_MODE, HMC5883L_MODE_MD_BIT, HMC5883L_MODE_MD_LEN, buffer);
    return buffer[0];
}

void HMC5883L::setMode(uint8_t mode) {
    writeBits(HMC5883L_RA_MODE, HMC5883L_MODE_MD_BIT, HMC5883L_MODE_MD_LEN, mode);
}

// DATA registers
void HMC5883L::getRawMeasurement(int16_t *rawField) {
    readBytes(HMC5883L_RA_DATAX_H, 6, buffer);
    rawField[0] = (((int16_t)buffer[0]) << 8) | buffer[1];
    rawField[1] = (((int16_t)buffer[4]) << 8) | buffer[5];
    rawField[2] = (((int16_t)buffer[2]) << 8) | buffer[3];
}

// STATUS registers
bool HMC5883L::getLockStatus() {
    readBit(HMC5883L_RA_STATUS, HMC5883L_STATUS_LOCK_BIT, buffer);
    return buffer[0];
}

bool HMC5883L::getReadyStatus() {
    readBit(HMC5883L_RA_STATUS, HMC5883L_STATUS_RDY_BIT, buffer);
    return buffer[0];
}

// Private
float HMC5883L::getScale(uint8_t gain) {
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

#endif // HMC5883L_INSTALLED
