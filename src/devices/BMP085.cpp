#include "config.h"
#include "application.h"

#ifdef BMP085_INSTALLED

#include "BMP085.h"

// Initialization
BMP085::BMP085() {
    this->address = BMP085_ADDRESS;
}

void BMP085::initialize() {
    loadCalibration();
}

bool BMP085::testConnection() {
    // TODO
    return true;
}

// Barometer
float BMP085::getPressure() {
    int32_t ut = getRawTemperature();
    int32_t up = getRawPressure();

    Serial.printlnf("ut=%d, up=%d", ut, up);

    // TODO
    return 0;
}

float BMP085::getTemperature() {
    float t;
    int16_t ut = getRawTemperature();
    int32_t b5 = computeB5(ut);

    t = (b5+8) >> 4;

    // Convert to C
    t /= 10;

    return t;
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

// CONTROL register
uint8_t BMP085::getControl() {
    readByte(BMP085_RA_CONTROL, buffer);
    return buffer[0];
}

void BMP085::setControl(uint8_t value) {
    writeByte(BMP085_RA_CONTROL, value);
    usleep(4500);
}

// DATA register
int32_t BMP085::getRawTemperature() {
    int16_t rawTemperature;

    setControl(BMP085_CONTROL_TEMPERATURE);
    readWordSigned(BMP085_RA_DATA, &rawTemperature);

    return rawTemperature;
}

// TODO: get this working
int32_t BMP085::getRawPressure() {
    int32_t rawPressure;

    setControl(BMP085_CONTROL_PRESSURE_0);

    readBytes(BMP085_RA_DATA, 3, buffer);
    rawPressure = ((uint32_t)buffer[0] << 16) + ((uint16_t)buffer[1] << 8) + buffer[2];

    return rawPressure;
}

// Private
int32_t BMP085::computeB5(int32_t ut) {
    int32_t x1 = (ut - (int32_t)ac6) * ((int32_t)ac5) >> 15;
    int32_t x2 = ((int32_t)mc << 11) / (x1+(int32_t)md);
    return x1 + x2;
}

#endif // BMP085_INSTALLED
