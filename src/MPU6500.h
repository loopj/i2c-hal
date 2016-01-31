#pragma once

#include "Sensor_Config.h"

#ifdef MPU6500_INSTALLED

#include <stdint.h>

#include "Accelerometer.h"
#include "Gyroscope.h"
#include "I2CDevice.h"
#include "Vector3.h"

// Device info
#define MPU6500_ADDRESS_AD0_LOW     0x68
#define MPU6500_ADDRESS_AD0_HIGH    0x68
#define MPU6500_DEFAULT_ADDRESS     MPU6500_ADDRESS_AD0_LOW
#define MPU6500_DEVICE_ID           0x70

// Register map
enum {
    MPU6500_RA_SELF_TEST_X_GYRO    = 0x00,
    MPU6500_RA_SELF_TEST_Y_GYRO    = 0x01,
    MPU6500_RA_SELF_TEST_Z_GYRO    = 0x02,
    MPU6500_RA_SELF_TEST_X_ACCEL   = 0x0D,
    MPU6500_RA_SELF_TEST_Y_ACCEL   = 0x0E,
    MPU6500_RA_SELF_TEST_Z_ACCEL   = 0x0F,
    MPU6500_RA_XG_OFFSET_H         = 0x13, // X_OFFS_USR[15:8]
    MPU6500_RA_XG_OFFSET_L         = 0x14, // X_OFFS_USR[7:0]
    MPU6500_RA_YG_OFFSET_H         = 0x15, // Y_OFFS_USR[15:8]
    MPU6500_RA_YG_OFFSET_L         = 0x16, // Y_OFFS_USR[7:0]
    MPU6500_RA_ZG_OFFSET_H         = 0x17, // Z_OFFS_USR[15:8]
    MPU6500_RA_ZG_OFFSET_L         = 0x18, // Z_OFFS_USR[7:0]
    MPU6500_RA_SMPLRT_DIV          = 0x19, // SMPLRT_DIV[7:0]
    MPU6500_RA_CONFIG              = 0x1A, // FIFO_MODE, EXT_SYNC_SET[2:0], DLPF_CFG[2:0]
    MPU6500_RA_GYRO_CONFIG         = 0x1B, // XG_ST, YG_ST, ZG_ST, GYRO_FS_SEL[1:0], FCHOICE_B[1:0]
    MPU6500_RA_ACCEL_CONFIG        = 0x1C, // XA_ST, YA_ST, ZA_ST, ACCEL_FS_SEL[1:0]
    MPU6500_RA_ACCEL_CONFIG_2      = 0x1D, // ACCEL_FCHOICE_B, A_DLPF_CFG
    MPU6500_RA_LP_ACCEL_ODR        = 0x1E, // LPOSC_CLKSEL[3:0]
    MPU6500_RA_WOM_THR             = 0x1F, // WOM_THRESHOLD[7:0]
    MPU6500_RA_FIFO_EN             = 0x23, // TEMP_FIFO_EN, GYRO_XOUT, GYRO_YOUT, GYRO_ZOUT, ACCEL, SLV2, SLV1, SLV0
    MPU6500_RA_I2C_MST_CTRL        = 0x24,
    MPU6500_RA_I2C_SLV0_ADDR       = 0x25,
    MPU6500_RA_I2C_SLV0_REG        = 0x26,
    MPU6500_RA_I2C_SLV0_CTRL       = 0x27,
    MPU6500_RA_I2C_SLV1_ADDR       = 0x28,
    MPU6500_RA_I2C_SLV1_REG        = 0x29,
    MPU6500_RA_I2C_SLV1_CTRL       = 0x2A,
    MPU6500_RA_I2C_SLV2_ADDR       = 0x2B,
    MPU6500_RA_I2C_SLV2_REG        = 0x2C,
    MPU6500_RA_I2C_SLV2_CTRL       = 0x2D,
    MPU6500_RA_I2C_SLV3_ADDR       = 0x2E,
    MPU6500_RA_I2C_SLV3_REG        = 0x2F,
    MPU6500_RA_I2C_SLV3_CTRL       = 0x30,
    MPU6500_RA_I2C_SLV4_ADDR       = 0x31,
    MPU6500_RA_I2C_SLV4_REG        = 0x32,
    MPU6500_RA_I2C_SLV4_DO         = 0x33,
    MPU6500_RA_I2C_SLV4_CTRL       = 0x34,
    MPU6500_RA_I2C_SLV4_DI         = 0x35,
    MPU6500_RA_I2C_MST_STATUS      = 0x36,
    MPU6500_RA_INT_PIN_CFG         = 0x37,
    MPU6500_RA_INT_ENABLE          = 0x38,
    MPU6500_RA_INT_STATUS          = 0x3A,
    MPU6500_RA_ACCEL_XOUT_H        = 0x3B, // ACCEL_XOUT_H[15:8]
    MPU6500_RA_ACCEL_XOUT_L        = 0x3C, // ACCEL_XOUT_L[7:0]
    MPU6500_RA_ACCEL_YOUT_H        = 0x3D, // ACCEL_YOUT_H[15:8]
    MPU6500_RA_ACCEL_YOUT_L        = 0x3E, // ACCEL_YOUT_L[7:0]
    MPU6500_RA_ACCEL_ZOUT_H        = 0x3F, // ACCEL_ZOUT_H[15:8]
    MPU6500_RA_ACCEL_ZOUT_L        = 0x40, // ACCEL_ZOUT_L[7:0]
    MPU6500_RA_TEMP_OUT_H          = 0x41, // TEMP_OUT_H[15:8]
    MPU6500_RA_TEMP_OUT_L          = 0x42, // TEMP_OUT_L[7:0]
    MPU6500_RA_GYRO_XOUT_H         = 0x43, // GYRO_XOUT_H[15:8]
    MPU6500_RA_GYRO_XOUT_L         = 0x44, // GYRO_XOUT_L[7:0]
    MPU6500_RA_GYRO_YOUT_H         = 0x45, // GYRO_YOUT_H[15:8]
    MPU6500_RA_GYRO_YOUT_L         = 0x46, // GYRO_YOUT_L[7:0]
    MPU6500_RA_GYRO_ZOUT_H         = 0x47, // GYRO_ZOUT_H[15:8]
    MPU6500_RA_GYRO_ZOUT_L         = 0x48, // GYRO_ZOUT_L[7:0]
    MPU6500_RA_EXT_SENS_DATA_00    = 0x49,
    MPU6500_RA_EXT_SENS_DATA_01    = 0x4A,
    MPU6500_RA_EXT_SENS_DATA_02    = 0x4B,
    MPU6500_RA_EXT_SENS_DATA_03    = 0x4C,
    MPU6500_RA_EXT_SENS_DATA_04    = 0x4D,
    MPU6500_RA_EXT_SENS_DATA_05    = 0x4E,
    MPU6500_RA_EXT_SENS_DATA_06    = 0x4F,
    MPU6500_RA_EXT_SENS_DATA_07    = 0x50,
    MPU6500_RA_EXT_SENS_DATA_08    = 0x51,
    MPU6500_RA_EXT_SENS_DATA_09    = 0x52,
    MPU6500_RA_EXT_SENS_DATA_10    = 0x53,
    MPU6500_RA_EXT_SENS_DATA_11    = 0x54,
    MPU6500_RA_EXT_SENS_DATA_12    = 0x55,
    MPU6500_RA_EXT_SENS_DATA_13    = 0x56,
    MPU6500_RA_EXT_SENS_DATA_14    = 0x57,
    MPU6500_RA_EXT_SENS_DATA_15    = 0x58,
    MPU6500_RA_EXT_SENS_DATA_16    = 0x59,
    MPU6500_RA_EXT_SENS_DATA_17    = 0x5A,
    MPU6500_RA_EXT_SENS_DATA_18    = 0x5B,
    MPU6500_RA_EXT_SENS_DATA_19    = 0x5C,
    MPU6500_RA_EXT_SENS_DATA_20    = 0x5D,
    MPU6500_RA_EXT_SENS_DATA_21    = 0x5E,
    MPU6500_RA_EXT_SENS_DATA_22    = 0x5F,
    MPU6500_RA_EXT_SENS_DATA_23    = 0x60,
    MPU6500_RA_I2C_SLV0_DO         = 0x63,
    MPU6500_RA_I2C_SLV1_DO         = 0x64,
    MPU6500_RA_I2C_SLV2_DO         = 0x65,
    MPU6500_RA_I2C_SLV3_DO         = 0x66,
    MPU6500_RA_I2C_MST_DELAY_CTRL  = 0x67,
    MPU6500_RA_SIGNAL_PATH_RESET   = 0x68,
    MPU6500_RA_ACCEL_INTEL_CTRL    = 0x69,
    MPU6500_RA_USER_CTRL           = 0x6A, // DMP_EN, FIFO_EN, I2C_MST_EN, I2C_IF_DIS, DMP_RST, FIFO_RST, I2C_MST_RST, SIG_COND_RST
    MPU6500_RA_PWR_MGMT_1          = 0x6B, // DEVICE_RESET, SLEEP, CYCLE, GYRO_STANDBY, TEMP_DIS, CLKSEL[2:0]
    MPU6500_RA_PWR_MGMT_2          = 0x6C,
    MPU6500_RA_FIFO_COUNT_H        = 0x72,
    MPU6500_RA_FIFO_COUNT_L        = 0x73,
    MPU6500_RA_FIFO_R_W            = 0x74,
    MPU6500_RA_WHO_AM_I            = 0x75,
    MPU6500_RA_XA_OFFSET_H         = 0x77,
    MPU6500_RA_XA_OFFSET_L         = 0x78,
    MPU6500_RA_YA_OFFSET_H         = 0x7A,
    MPU6500_RA_YA_OFFSET_L         = 0x7B,
    MPU6500_RA_ZA_OFFSET_H         = 0x7D,
    MPU6500_RA_ZA_OFFSET_L         = 0x7E
};

// GYRO_CONFIG
#define MPU6500_GYRO_FS_SEL_BIT     4
#define MPU6500_GYRO_FS_SEL_LEN     2

// GYRO_CONFIG FS_SEL
#define MPU6500_GYRO_FS_250         0x00
#define MPU6500_GYRO_FS_500         0x01
#define MPU6500_GYRO_FS_1000        0x02
#define MPU6500_GYRO_FS_2000        0x03

// ACCEL_CONFIG
#define MPU6500_ACCEL_FS_SEL_BIT    4
#define MPU6500_ACCEL_FS_SEL_LEN    2

// ACCEL_CONFIG AFS_SEL
#define MPU6500_ACCEL_FS_2          0x00
#define MPU6500_ACCEL_FS_4          0x01
#define MPU6500_ACCEL_FS_8          0x02
#define MPU6500_ACCEL_FS_16         0x03

// INT_PIN_CFG
#define MPU6500_BYPASS_EN_BIT       1

// USER_CTRL
#define MPU6500_DMP_EN_BIT          7
#define MPU6500_FIFO_EN_BIT         6

// PWR_MGMT_1
#define MPU6500_DEVICE_RESET_BIT    7
#define MPU6500_SLEEP_BIT           6
#define MPU6500_CLKSEL_BIT          2
#define MPU6500_CLKSEL_LEN          3
#define MPU6500_CLOCK_INTERNAL      0x00
#define MPU6500_CLOCK_PLL           0x01
#define MPU6500_CLOCK_KEEP_RESET    0x07

class MPU6500 : public I2CDevice, public Accelerometer, public Gyroscope {
public:
    static MPU6500& getInstance() {
        static MPU6500 instance;
        return instance;
    }

    // Initialization
    MPU6500(uint8_t address = MPU6500_DEFAULT_ADDRESS);
    void initialize();
    bool testConnection();

    // Accelerometer
    Vector3 getAcceleration();

    // Gyroscope
    Vector3 getRotation();

    // GYRO_CONFIG register
    uint8_t getFullScaleGyroRange();
    void setFullScaleGyroRange(uint8_t range);

    // ACCEL_CONFIG register
    uint8_t getFullScaleAccelRange();
    void setFullScaleAccelRange(uint8_t range);

    // INT_PIN_CFG register
    bool getI2cBypassEnabled();
    void setI2cBypassEnabled(bool enabled);

    // USER_CTRL register
    bool getDMPEnabled();
    void setDMPEnabled(bool enabled);

    // PWR_MGMT_1 register
    void reset();
    bool getSleepEnabled();
    void setSleepEnabled(bool enabled);
    uint8_t getClockSource();
    void setClockSource(uint8_t source);

    // WHO_AM_I register
    uint8_t getDeviceID();

protected:
    float getGyroScale(uint8_t gyroRange);
    float getAccelScale(uint8_t accelRange);
    float accelScale;
    float gyroScale;
};

#endif // MPU6500_INSTALLED
