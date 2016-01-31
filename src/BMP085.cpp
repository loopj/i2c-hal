#include "Sensor_Config.h"

#ifdef BMP085_INSTALLED

#include "BMP085.h"

// Initialization
BMP085::BMP085() {
    this->address = BMP085_ADDRESS;
}

void BMP085::initialize() {
    loadCalibration();
    setOversamplingMode(BMP085_MODE_STANDARD);
}

bool BMP085::testConnection() {
    return getDeviceID() == BMP085_DEVICE_ID;
}

// Barometer
float BMP085::getPressure() {
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
float BMP085::getTemperature() {
    int16_t ut = getRawTemperature();

    // Calculate true temperature, according to datasheet rules
    int32_t b5 = computeB5(ut);
    float t = (b5+8) >> 4;

    // Convert to C
    return t / 10.0;
}

// CAL registers
void BMP085::loadCalibration() {
    readWordSigned(BMP085_RA_CAL_AC1, &ac1);
    readWordSigned(BMP085_RA_CAL_AC2, &ac2);
    readWordSigned(BMP085_RA_CAL_AC3, &ac3);
    readWord(BMP085_RA_CAL_AC4, &ac4);
    readWord(BMP085_RA_CAL_AC5, &ac5);
    readWord(BMP085_RA_CAL_AC6, &ac6);
    readWordSigned(BMP085_RA_CAL_B1, &b1);
    readWordSigned(BMP085_RA_CAL_B2, &b2);
    readWordSigned(BMP085_RA_CAL_MB, &mb);
    readWordSigned(BMP085_RA_CAL_MC, &mc);
    readWordSigned(BMP085_RA_CAL_MD, &md);
}

// CHIPID register
uint8_t BMP085::getDeviceID() {
    readByte(BMP085_RA_CHIPID, buffer);
    return buffer[0];
}

// CONTROL register
uint8_t BMP085::getControl() {
    readByte(BMP085_RA_CONTROL, buffer);
    return buffer[0];
}

void BMP085::setControl(uint8_t value) {
    writeByte(BMP085_RA_CONTROL, value);
}

void BMP085::setOversamplingMode(uint8_t mode) {
    oss = mode;
}

// DATA registers
int32_t BMP085::getRawTemperature() {
    int16_t rawTemperature;

    // Start temperature measurement
    setControl(BMP085_CONTROL_TEMPERATURE);

    // Wait for the conversion to complete
    usleep(4500);

    // Read the raw temperature data;
    readWordSigned(BMP085_RA_DATA, &rawTemperature);

    return rawTemperature;
}

int32_t BMP085::getRawPressure() {
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

// Private
int32_t BMP085::computeB5(int32_t ut) {
    int32_t x1 = (ut - (int32_t)ac6) * ((int32_t)ac5) >> 15;
    int32_t x2 = ((int32_t)mc << 11) / (x1+(int32_t)md);
    return x1 + x2;
}

#endif // BMP085_INSTALLED
