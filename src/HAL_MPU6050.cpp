#include "config.h"

#ifdef MPU6050_INSTALLED

#include "HAL_MPU6050.h"

void HAL_MPU6050::initialize() {
    device.initialize();

    // Allow direct access to other sensors on the i2c bus
    device.setI2CBypassEnabled(true);

    accelScale = 2048.0 * pow(2, 3 - device.getFullScaleAccelRange());
    gyroScale = 16.4 * pow(2, 3 - device.getFullScaleGyroRange());
}

void HAL_MPU6050::groundCalibrate() {
    // Reset device registers and initialize device
    device.reset();
    device.initialize();

    // Set low-pass filter to 188 Hz
    device.setDLPFMode(MPU6050_DLPF_BW_188);

    // Set sample rate to 1 kHz
    device.setRate(0);

    // Wait for stable gyroscope data
    delay(200);

    // Enable FIFO
    device.setFIFOEnabled(true);

    // Enable gyro and accelerometer sensors for FIFO
    device.setAccelFIFOEnabled(true);
    device.setXGyroFIFOEnabled(true);
    device.setYGyroFIFOEnabled(true);
    device.setZGyroFIFOEnabled(true);

    // Accumulate 80 samples in 80 milliseconds = 960 bytes (max fifo size is 1024)
    delay(80);

    // Disable gyro and accelerometer sensors for FIFO
    device.setAccelFIFOEnabled(false);
    device.setXGyroFIFOEnabled(false);
    device.setYGyroFIFOEnabled(false);
    device.setZGyroFIFOEnabled(false);

    // Combine all packets of calibration data
    int32_t gyroBias[3] = {0, 0, 0}, accelBias[3] = {0, 0, 0};
    uint16_t packetCount = device.getFIFOCount()/12;
    for(int i=0; i<packetCount; i++) {
        // Read this packet's gyro and accel data
        int16_t accelTemp[3] = {0, 0, 0}, gyroTemp[3] = {0, 0, 0};
        I2Cdev::readWords(MPU6050_ADDRESS_AD0_LOW, MPU6050_RA_FIFO_R_W, 3, (uint16_t *)accelTemp);
        I2Cdev::readWords(MPU6050_ADDRESS_AD0_LOW, MPU6050_RA_FIFO_R_W, 3, (uint16_t *)gyroTemp);

        // Add this packet to the bias totals
        for(int d=0; d<3; d++) {
            accelBias[d] += accelTemp[d];
            gyroBias[d] += gyroTemp[d];
        }
    }

    // Average the calibration data
    for(int d=0; d<3; d++) {
        accelBias[d] /= packetCount;
        gyroBias[d] /= packetCount;
    }

    // Disable FIFO
    device.setFIFOEnabled(false);

    // Remove gravity from z-axis of accelerometer bias
    uint16_t accelSensitivity = 16384;  // = 1g
    accelBias[2] > 0 ? accelBias[2] -= accelSensitivity : accelBias[2] += accelSensitivity;

    // Push gyro biases to hardware registers
    // Divide by 4 to get 32.9 LSB per deg/s to conform to expected bias input format
    device.setXGyroOffset(-gyroBias[0] / 4);
    device.setYGyroOffset(-gyroBias[1] / 4);
    device.setZGyroOffset(-gyroBias[2] / 4);

    // Read factory accelerometer trim values
    // Write total accelerometer bias, including calculated average accelerometer bias from above
    // Subtract calculated averaged accelerometer bias scaled to 2048 LSB/g (16 g full scale)
    device.setXAccelOffset(device.getXAccelOffset() - (accelBias[0] / 8));
    device.setYAccelOffset(device.getYAccelOffset() - (accelBias[1] / 8));
    device.setZAccelOffset(device.getZAccelOffset() - (accelBias[2] / 8));
}

Vector3 HAL_MPU6050::getAcceleration() {
    // Get the raw accelerometer readings
    int16_t rax, ray, raz;
    device.getAcceleration(&rax, &ray, &raz);

    // Convert raw accelerometer readings into Gs
    return Vector3(ACCELEROMETER_ORIENTATION((double)rax/accelScale, (double)ray/accelScale, (double)raz/accelScale));
}

Vector3 HAL_MPU6050::getRotation() {
    // Get the raw gyroscope readings
    int16_t rgx, rgy, rgz;
    device.getRotation(&rgx, &rgy, &rgz);

    // Convert raw gyroscope readings into degrees per second
    return Vector3(GYROSCOPE_ORIENTATION((double)rgx/gyroScale, (double)rgy/gyroScale, (double)rgz/gyroScale));
}

#endif // MPU6050_INSTALLED
