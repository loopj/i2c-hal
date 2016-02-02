# I2C Sensor Abstraction Layer

[![Build Status](https://travis-ci.org/loopj/i2c-sensor-hal.svg?branch=master)](https://travis-ci.org/loopj/i2c-sensor-hal)

This library allows you to use sensors like accelerometers, gyroscopes, and barometers in your [Arduino](https://www.arduino.cc/) and [Particle](https://www.particle.io/) projects, without knowing the intimate details about the sensor chip. Say goodbye to reading device data-sheets or learning complex I2C interactions.

Sensor functions always return [SI units](https://en.wikipedia.org/wiki/International_System_of_Units), so no extra conversions are required in most situations.

## Contents

- [Usage](#usage)
- [Sensors](#sensors)
- [Devices](#devices)
- [Platforms](#platforms)
- [Contributing](#contributing)
- [License](#license)


## Usage

First you'll need to define which [devices](#devices) are installed:

```c++
#define MPU6500_INSTALLED
#define AK8963_INSTALLED
```

Then you can use [sensors](#sensors) as follows:

```c++
Accelerometer *accelerometer = Sensors::getAccelerometer();
Vector3 acceleration = accelerometer->getAcceleration();
```


## Sensors

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


## Devices

The following I2C devices are currently supported by this library:

### AK8963

- Magnetometer
- `#define AK8963_INSTALLED`

### BMP085

- Barometer, Thermometer
- `#define BMP085_INSTALLED`
- Probably also compatible with BMP180

### HMC5883L

- Magnetometer
- `#define HMC5883L_INSTALLED`

### MPU6500

- Accelerometer, Gyroscope
- `#define MPU6500_INSTALLED`
- Probably also compatible with MPU6050


## Platforms

### Confirmed Working

This library has been tested on the following platforms and development boards:

#### Atmel AVR

- [Arduino Micro](https://www.arduino.cc/en/Main/ArduinoBoardMicro)

#### Particle

- [Particle Core](https://docs.particle.io/datasheets/core-datasheet/)
- [Particle Photon](https://docs.particle.io/datasheets/photon-datasheet/)

#### ESP8266

- [ESP8266](https://en.wikipedia.org/wiki/ESP8266)

#### Teensy

- [Teensy 3.2 / 3.1](https://www.pjrc.com/teensy/teensy31.html)

### Other Devices

There is a good chance this library will also work "out of the box" with most devices using an Arduino-based framework.

If you'd like to add support for a new platform, you can implement the underlying I2C functions for your platform, take a look at  for examples.


## Contributing

We'd love you to file issues and send pull requests. The [contributing guidelines](CONTRIBUTING.md) details the process of building and testing this library, as well as the pull request process. Feel free to comment on [existing issues](https://github.com/loopj/i2cdevlib-hal/issues) for clarification or starting points.


## License

This library is free software released under the MIT License. See [LICENSE.txt](LICENSE.txt) for details.
