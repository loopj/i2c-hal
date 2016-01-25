# I2C Sensor Abstraction Layer

[![Project Status: WIP - Initial development is in progress, but there has not yet been a stable, usable release suitable for the public.](http://www.repostatus.org/badges/latest/wip.svg)](http://www.repostatus.org/#wip)

This library allows you to use sensors like accelerometers, gyroscopes, and barometers without knowing the intimate details about the actual device connected, or having to have to read device data-sheets or learn complex I2C interactions.

Inspired by the awesome [i2cdevlib](https://github.com/jrowberg/i2cdevlib) library by Jeff Rowberg.

## Contents

- [Usage](#usage)
- [Sensors](#sensors)
- [Devices](#devices)
- [Platforms](#platforms)
- [Contributing](#contributing)
- [License](#license)


## Usage

First you'll need to define which sensor devices are installed:

```c++
#define MPU6500_INSTALLED
#define AK8963_INSTALLED
```

Then you can use sensors as describe below.


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

A [barometer](https://en.wikipedia.org/wiki/Barometer) measures [atmospheric pressure](https://en.wikipedia.org/wiki/Atmospheric_pressure) in hPa or mbar.

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

A [gyroscope](https://en.wikipedia.org/wiki/Gyroscope) measures the [rotational speed](https://en.wikipedia.org/wiki/Rotational_speed) in rad/s, on three axes.

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

A [thermometer](https://en.wikipedia.org/wiki/Thermometer) measures [temperature](https://en.wikipedia.org/wiki/Temperature) in °C.

```c++
// Get access to the thermometer
Thermometer *thermometer = Sensors::getThermometer();

// Get the current temperature, in °C
float temperature = thermometer->getTemperature();
```


## Devices

This library supports the following I2C devices:

- AK8963 (Magnetometer)
- BMP085 (Barometer)
- HMC5883L (Magnetometer)
- MPU6500 (Accelerometer, Gyroscope)


## Platforms

This library has been tested on the following devices:

- [Particle Core](https://docs.particle.io/datasheets/core-datasheet/)
- [Particle Photon](https://docs.particle.io/datasheets/photon-datasheet/)

There is a good chance this library will also work "out of the box" with Arduino devices. If you'd like to add support for a new platform, you can implement the underlying I2C functions for your platform, take a look in `src/platforms` for examples.


## Contributing

We'd love you to file issues and send pull requests. The [contributing guidelines](CONTRIBUTING.md) details the process of building and testing this library, as well as the pull request process. Feel free to comment on [existing issues](https://github.com/loopj/i2cdevlib-hal/issues) for clarification or starting points.


## License

This library is free software released under the MIT License. See [LICENSE.txt](LICENSE.txt) for details.
