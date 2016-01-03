#pragma once

//
// Configure which sensor devices are installed
//

// MPU6050/MPU6500 - Accelerometer/Gyroscope
// #define MPU6050_INSTALLED

// AK8963 - Compass
// #define AK8963_INSTALLED

// AK8975 - Compass
// #define AK8975_INSTALLED

// BMP085/BMP180 - Barometer
// #define BMP085_INSTALLED

// HMC5883L - Compass
// #define HMC5883L_INSTALLED

// MPU9250 - Accelerometer/Gyroscope/Compass (MPU6050 + AK8963)
// #define MPU6050_INSTALLED
// #define AK8975_INSTALLED

// MPU9250 - Accelerometer/Gyroscope/Compass (MPU6500 + AK8963)
#define MPU6050_INSTALLED
#define AK8963_INSTALLED


//
// Configure the orientation of sensor devices
//

#define ACCELEROMETER_ORIENTATION(X,Y,Z) X,-Y,-Z
#define GYROSCOPE_ORIENTATION(X,Y,Z) X,-Y,-Z
#define COMPASS_ORIENTATION(X,Y,Z) X,Y,Z
