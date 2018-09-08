# I2C Abstraction Layer

[![Build Status](https://travis-ci.org/loopj/i2c-hal.svg?branch=master)](https://travis-ci.org/loopj/i2c-hal)

This library allows you to use I2C devices such as accelerometers, gyroscopes, and barometers in your [Arduino][1], [ESP8266][2], [mbed][9], [Particle][3] and [Raspberry Pi][4] projects, without knowing the intimate details about the sensor chip. Say goodbye to reading device data-sheets or learning complex I2C interactions.

Prototype on Arduino or Particle and use the same code when moving to production.

Sensor functions always return [SI units](https://en.wikipedia.org/wiki/International_System_of_Units), so no extra conversions are required in most situations.

## Contents

- [Getting Started](#getting-started)
  - [Installation](#installation)
  - [Usage](#usage)
- [Sensors](#sensors)
  - [Accelerometer](#accelerometer)
  - [Barometer](#barometer)
  - [Gyroscope](#gyroscope)
  - [Magnetometer](#magnetometer)
  - [Thermometer](#thermometer)
- [Supported Devices](#supported-devices)
- [Platforms, Frameworks & Boards](#platforms-frameworks--boards)
- [Contributing](#contributing)
- [License](#license)

## Getting Started

### Installation

#### Using PlatformIO

The recommended way to use this library is with [PlatformIO](http://platformio.org/):

```shell
$ platformio lib install 578
```

#### Using the Arduino Library Manager

If you are using the Arduino IDE, find `Sensors` by James Smith in the Library Manager and click install.

#### Manual Installation

If you can't use PlatformIO or Arduino Library Manager, you can always simply copy the library into your project or include it as a git submodule. This is the preferred approach for the Particle platform, as you can see in the [particle example app ](https://github.com/loopj/i2c-sensor-hal/tree/master/examples/particle).

## Usage

Once you've installed the library, you'll need to define which sensor devices are installed (see [supported devices](#supported-devices)) and then include `Sensors.h`:

```c++
#define SENSORS_MPU6050_ATTACHED
#define SENSORS_BMP085_ATTACHED
#include <Sensors.h>
```

You'll then be able to use sensors as follows:

```c++
Accelerometer *accelerometer = Sensors::getAccelerometer();
Vector3 acceleration = accelerometer->getAcceleration();
```

See the [sensor types](#sensor-types) section below for details on each sensor type, and check out the [example apps folder](https://github.com/loopj/i2c-sensor-hal/tree/master/examples) for some complete examples.


## Sensors

The following sensor types are currently supported by this library:

### Accelerometer

An [accelerometer](https://en.wikipedia.org/wiki/Accelerometer) measures [proper acceleration](https://en.wikipedia.org/wiki/Proper_acceleration) (including gravity) in m/s², on three axes.

```c++
// Get access to the accelerometer
Accelerometer *accelerometer = Sensors::getAccelerometer();

// Get the current acceleration vector (x/y/z), in m/s^2
Vector3 acceleration = accelerometer->getAcceleration();
```

### Barometer

A [barometer](https://en.wikipedia.org/wiki/Barometer) measures [atmospheric pressure](https://en.wikipedia.org/wiki/Atmospheric_pressure) in [hPa](https://en.wikipedia.org/wiki/Pascal_(unit)) (or millibars).

Using atmospheric pressure from a barometer, you can also compute the [altitude](https://en.wikipedia.org/wiki/Altitude) in meters.

```c++
// Get access to the barometer
Barometer *barometer = Sensors::getBarometer();

// Get the current ambient air pressure in hPA (mbar)
float pressure = barometer->getPressure();

// Get the current altitude in m, based on the standard baseline pressure
float altitude = barometer->getAltitude();

// Get the current altitude in m, based on a provided baseline pressure
float altitude = barometer->getAltitude(baselinePressure);

// Get the pressure at sea-level in hPa, given the current altitude
float sealevelPressure = barometer->getSealevelPressure(altitude);
```

### Gyroscope

A [gyroscope](https://en.wikipedia.org/wiki/Gyroscope) measures the [rotational speed](https://en.wikipedia.org/wiki/Rotational_speed) in [rad/s](https://en.wikipedia.org/wiki/Radian_per_second), on three axes.

```c++
// Get access to the gyroscope
Gyroscope *gyroscope = Sensors::getGyroscope();

// Get the current rotation rate vector (x/y/z), in rad/s
Vector3 rotation = gyroscope->getRotation();
```

### Magnetometer

A [magnetometer](https://en.wikipedia.org/wiki/Magnetometer) measures the strength and direction of [magnetic fields](https://en.wikipedia.org/wiki/Magnetic_field) in [μT](https://en.wikipedia.org/wiki/Tesla_(unit)), on three axes.

Using magnetic field readings from a magnetometer, you can also compute the [azimuth](https://en.wikipedia.org/wiki/Azimuth) (or compass direction) of your device.

```c++
// Get access to the magnetometer
Magnetometer *magnetometer = Sensors::getMagnetometer();

// Get the current magnetic field strength vector (x/y/z), in μT
Vector3 magneticField = magnetometer->getMagneticField();

// Get the current azimuth (compass direction), optionally adjusting for declination
float azimuth = magnetometer->getAzimuth();
```

### Thermometer

A [thermometer](https://en.wikipedia.org/wiki/Thermometer) measures [temperature](https://en.wikipedia.org/wiki/Temperature) in [°C](https://en.wikipedia.org/wiki/Celsius).

```c++
// Get access to the thermometer
Thermometer *thermometer = Sensors::getThermometer();

// Get the current temperature, in °C
float temperature = thermometer->getTemperature();
```


## Supported Devices

The following I2C devices are currently supported by this library:

| Device    | Provides Sensors                          | #define
|---------- |----------------------------------------   |--------------------------
| AK8963    | Magnetometer                              | SENSORS_AK8963_ATTACHED
| BMP085    | Barometer, Thermometer                    | SENSORS_BMP085_ATTACHED
| BMP180    | Barometer, Thermometer                    | SENSORS_BMP180_ATTACHED
| HMC5883L  | Magnetometer                              | SENSORS_HMC5883L_ATTACHED
| MPU6050   | Accelerometer, Gyroscope                  | SENSORS_MPU6050_ATTACHED
| MPU6500   | Accelerometer, Gyroscope                  | SENSORS_MPU6500_ATTACHED
| MPU9150   | Accelerometer, Gyroscope, Magnetometer    | SENSORS_MPU9150_ATTACHED
| MPU9250   | Accelerometer, Gyroscope, Magnetometer    | SENSORS_MPU9250_ATTACHED

If you'd like to see another sensor device supported here, see the [contributing](#contributing) section below.


## Platforms, Frameworks & Boards

This library supports almost every popular embedded platform, including the following development boards:

| Platform          | Boards
|-------------------|----------------------------------------------------------
| [Arduino][1]      | Any [Atmel AVR][6] or [Atmel SAM][10] based Ardunio, or Arduino-like board
| [ESP8266][2]      | Any [ESP8266 based][7] board
| [mbed][9]         | Most boards using the ARM mbed framework
| [Particle][3]     | Particle Core, Particle Photon, Particle Electron
| [Raspberry Pi][4] | Any board which support [WiringPi][8]
| [Teensy][5]       | Any Teensy board

If you test a new platform or development board and can confirm it works, please let me know in [an issue](https://github.com/loopj/i2cdevlib-hal/issues) and I'll update this documentation.


## Contributing

I'd love you to file issues and send pull requests. The [contributing guidelines](CONTRIBUTING.md) details the process of adding support for sensors, devices and frameworks, building and testing the library, as well as the pull request process. Feel free to comment on [existing issues](https://github.com/loopj/i2c-hal/issues) for clarification or starting points.


## License

This library is free software released under the MIT License. See [LICENSE.txt](LICENSE.txt) for details.


[1]: https://www.arduino.cc/
[2]: https://en.wikipedia.org/wiki/ESP8266
[3]: https://www.particle.io/
[4]: https://www.raspberrypi.org/
[5]: https://www.pjrc.com/teensy/
[6]: http://platformio.org/#!/boards?filter%5Bplatform%5D=atmelavr
[7]: http://platformio.org/#!/boards?filter%5Bplatform%5D=espressif
[8]: http://wiringpi.com/
[9]: https://www.mbed.com/
[10]: http://platformio.org/#!/boards?filter%5Bplatform%5D=atmelsam
