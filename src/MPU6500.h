#pragma once

#ifdef MPU6500_INSTALLED

#include <stdint.h>

#include "Accelerometer.h"
#include "Gyroscope.h"
#include "I2CDevice.h"
#include "Vector3.h"

class MPU6500 : public I2CDevice, public Accelerometer, public Gyroscope {
public:
    static MPU6500& getInstance() {
        static MPU6500 instance;
        return instance;
    }

    // I2C address
    static const int ADDRESS_AD0_LOW    = 0x68;
    static const int ADDRESS_AD0_HIGH   = 0x68;
    static const int DEFAULT_ADDRESS    = ADDRESS_AD0_LOW;

    // Register map
    enum Registers {
        RA_SELF_TEST_X_GYRO    = 0x00,
        RA_SELF_TEST_Y_GYRO    = 0x01,
        RA_SELF_TEST_Z_GYRO    = 0x02,
        RA_SELF_TEST_X_ACCEL   = 0x0D,
        RA_SELF_TEST_Y_ACCEL   = 0x0E,
        RA_SELF_TEST_Z_ACCEL   = 0x0F,
        RA_XG_OFFSET_H         = 0x13,
        RA_XG_OFFSET_L         = 0x14,
        RA_YG_OFFSET_H         = 0x15,
        RA_YG_OFFSET_L         = 0x16,
        RA_ZG_OFFSET_H         = 0x17,
        RA_ZG_OFFSET_L         = 0x18,
        RA_SMPLRT_DIV          = 0x19,
        RA_CONFIG              = 0x1A,
        RA_GYRO_CONFIG         = 0x1B,
        RA_ACCEL_CONFIG        = 0x1C,
        RA_ACCEL_CONFIG_2      = 0x1D,
        RA_LP_ACCEL_ODR        = 0x1E,
        RA_WOM_THR             = 0x1F,
        RA_FIFO_EN             = 0x23,
        RA_I2C_MST_CTRL        = 0x24,
        RA_I2C_SLV0_ADDR       = 0x25,
        RA_I2C_SLV0_REG        = 0x26,
        RA_I2C_SLV0_CTRL       = 0x27,
        RA_I2C_SLV1_ADDR       = 0x28,
        RA_I2C_SLV1_REG        = 0x29,
        RA_I2C_SLV1_CTRL       = 0x2A,
        RA_I2C_SLV2_ADDR       = 0x2B,
        RA_I2C_SLV2_REG        = 0x2C,
        RA_I2C_SLV2_CTRL       = 0x2D,
        RA_I2C_SLV3_ADDR       = 0x2E,
        RA_I2C_SLV3_REG        = 0x2F,
        RA_I2C_SLV3_CTRL       = 0x30,
        RA_I2C_SLV4_ADDR       = 0x31,
        RA_I2C_SLV4_REG        = 0x32,
        RA_I2C_SLV4_DO         = 0x33,
        RA_I2C_SLV4_CTRL       = 0x34,
        RA_I2C_SLV4_DI         = 0x35,
        RA_I2C_MST_STATUS      = 0x36,
        RA_INT_PIN_CFG         = 0x37,
        RA_INT_ENABLE          = 0x38,
        RA_INT_STATUS          = 0x3A,
        RA_ACCEL_XOUT_H        = 0x3B,
        RA_ACCEL_XOUT_L        = 0x3C,
        RA_ACCEL_YOUT_H        = 0x3D,
        RA_ACCEL_YOUT_L        = 0x3E,
        RA_ACCEL_ZOUT_H        = 0x3F,
        RA_ACCEL_ZOUT_L        = 0x40,
        RA_TEMP_OUT_H          = 0x41,
        RA_TEMP_OUT_L          = 0x42,
        RA_GYRO_XOUT_H         = 0x43,
        RA_GYRO_XOUT_L         = 0x44,
        RA_GYRO_YOUT_H         = 0x45,
        RA_GYRO_YOUT_L         = 0x46,
        RA_GYRO_ZOUT_H         = 0x47,
        RA_GYRO_ZOUT_L         = 0x48,
        RA_EXT_SENS_DATA_00    = 0x49,
        RA_EXT_SENS_DATA_01    = 0x4A,
        RA_EXT_SENS_DATA_02    = 0x4B,
        RA_EXT_SENS_DATA_03    = 0x4C,
        RA_EXT_SENS_DATA_04    = 0x4D,
        RA_EXT_SENS_DATA_05    = 0x4E,
        RA_EXT_SENS_DATA_06    = 0x4F,
        RA_EXT_SENS_DATA_07    = 0x50,
        RA_EXT_SENS_DATA_08    = 0x51,
        RA_EXT_SENS_DATA_09    = 0x52,
        RA_EXT_SENS_DATA_10    = 0x53,
        RA_EXT_SENS_DATA_11    = 0x54,
        RA_EXT_SENS_DATA_12    = 0x55,
        RA_EXT_SENS_DATA_13    = 0x56,
        RA_EXT_SENS_DATA_14    = 0x57,
        RA_EXT_SENS_DATA_15    = 0x58,
        RA_EXT_SENS_DATA_16    = 0x59,
        RA_EXT_SENS_DATA_17    = 0x5A,
        RA_EXT_SENS_DATA_18    = 0x5B,
        RA_EXT_SENS_DATA_19    = 0x5C,
        RA_EXT_SENS_DATA_20    = 0x5D,
        RA_EXT_SENS_DATA_21    = 0x5E,
        RA_EXT_SENS_DATA_22    = 0x5F,
        RA_EXT_SENS_DATA_23    = 0x60,
        RA_I2C_SLV0_DO         = 0x63,
        RA_I2C_SLV1_DO         = 0x64,
        RA_I2C_SLV2_DO         = 0x65,
        RA_I2C_SLV3_DO         = 0x66,
        RA_I2C_MST_DELAY_CTRL  = 0x67,
        RA_SIGNAL_PATH_RESET   = 0x68,
        RA_ACCEL_INTEL_CTRL    = 0x69,
        RA_USER_CTRL           = 0x6A,
        RA_PWR_MGMT_1          = 0x6B,
        RA_PWR_MGMT_2          = 0x6C,
        RA_FIFO_COUNT_H        = 0x72,
        RA_FIFO_COUNT_L        = 0x73,
        RA_FIFO_R_W            = 0x74,
        RA_WHO_AM_I            = 0x75,
        RA_XA_OFFSET_H         = 0x77,
        RA_XA_OFFSET_L         = 0x78,
        RA_YA_OFFSET_H         = 0x7A,
        RA_YA_OFFSET_L         = 0x7B,
        RA_ZA_OFFSET_H         = 0x7D,
        RA_ZA_OFFSET_L         = 0x7E
    };

    #define MPU6500_PWR1_DEVICE_RESET_BIT   7
    #define MPU6500_PWR1_SLEEP_BIT          6
    #define MPU6500_PWR1_CYCLE_BIT          5
    #define MPU6500_PWR1_GYRO_STANDBY_BIT   3
    #define MPU6500_PWR1_TEMP_DIS_BIT       3
    #define MPU6500_PWR1_CLKSEL_BIT         2
    #define MPU6500_PWR1_CLKSEL_LENGTH      3

    #define MPU6500_GCONFIG_FS_SEL_BIT      4
    #define MPU6500_GCONFIG_FS_SEL_LENGTH   2

    #define MPU6050_ACONFIG_XA_ST_BIT           7
    #define MPU6050_ACONFIG_YA_ST_BIT           6
    #define MPU6050_ACONFIG_ZA_ST_BIT           5
    #define MPU6050_ACONFIG_AFS_SEL_BIT         4
    #define MPU6050_ACONFIG_AFS_SEL_LENGTH      2
    #define MPU6050_ACONFIG_ACCEL_HPF_BIT       2
    #define MPU6050_ACONFIG_ACCEL_HPF_LENGTH    3

    MPU6500(uint8_t address = DEFAULT_ADDRESS);
    void initialize();
    Vector3 getAcceleration();
    Vector3 getRotation();

private:
    double accelScale;
    double gyroScale;
    void setSleepEnabled(bool enabled);
    uint8_t getFullScaleGyroRange();
    uint8_t getFullScaleAccelRange();
};

#endif // MPU6500_INSTALLED
