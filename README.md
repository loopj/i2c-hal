# I2C Sensor Abstraction Layer

[![Project Status: WIP - Initial development is in progress, but there has not yet been a stable, usable release suitable for the public.](http://www.repostatus.org/badges/latest/wip.svg)](http://www.repostatus.org/#wip)

This library allows you to use sensors like accelerometers, gyroscopes, and barometers without knowing the intimate details about the actual device connected, or having to have to read device data-sheets or learn complex I2C interactions.

Inspired by the awesome [i2cdevlib](https://github.com/jrowberg/i2cdevlib) library by Jeff Rowberg.

## Contents

- [Usage](#usage)
- [Sensors](#sensors)
- [Coordinates](#coordinates)
- [Devices](#devices)
- [Platforms](#platforms)
- [Contributing](#contributing)
- [License](#license)


## Usage

First you'll need to define which sensor devices are installed:

```c++
#define MPU6050_INSTALLED
#define AK8963_INSTALLED
#define BMP085_INSTALLED
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

// Get the current ambient air pressure, in hPA/mbar
float pressure = barometer->getPressure();

// Get the current altitude based on a standard baseline, in m
float altitude = barometer->getAltitude();

// Get the current altitude based on a provided baseline, in m
float altitude = barometer->getAltitude(baselinePressure);
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

A [magnetometer](https://en.wikipedia.org/wiki/Magnetometer) measures the strength and direction of [magnetic fields](https://en.wikipedia.org/wiki/Magnetic_field) in [μT](https://en.wikipedia.org/wiki/Tesla_(unit), on three axes.

Using magnetic field readings from a magnetometer, you can also compute the [azimuth](https://en.wikipedia.org/wiki/Azimuth) (or compass direction) of your device.

```c++
// Get access to the magnetometer
Magnetometer *magnetometer = Sensors::getMagnetometer();

// Get the current magnetic field strength vector (x/y/z), in μT
Vector3 magneticField = gyroscope->getMagneticField();
```

### Thermometer

A [thermometer](https://en.wikipedia.org/wiki/Thermometer) measures [temperature](https://en.wikipedia.org/wiki/Temperature) in °C.

```c++
// Get access to the thermometer
Thermometer *thermometer = Sensors::getThermometer();

// Get the current temperature, in °C
float temperature = thermometer->getTemperature();
```


## Coordinates

TODO - describe coordinate system.


## Devices

TODO - describe supported devices

### AK8963
### AK8975
### BMP085 / BMP180
### HMC5883L
### MPU6050


## Platforms

This library currently only supports the Arduino and Particle platforms.

TODO - explain how to add additional platforms.


## Contributing

We'd love you to file issues and send pull requests. The [contributing guidelines](CONTRIBUTING.md) details the process of building and testing this library, as well as the pull request process. Feel free to comment on [existing issues](https://github.com/loopj/i2cdevlib-hal/issues) for clarification or starting points.


## License

This library is free software released under the MIT License. See [LICENSE.txt](LICENSE.txt) for details.
