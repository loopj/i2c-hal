# Contributing

-   [Fork](https://help.github.com/articles/fork-a-repo) the library
-   Build and test your changes
-   Commit and push until you are happy with your contribution
-   [Make a pull request](https://help.github.com/articles/using-pull-requests)
-   Thanks!

### Adding a New Sensor Device

Adding a new sensor device is fairly simple if you are familiar with I2C operations and device datasheets. Make a new [header only](https://en.wikipedia.org/wiki/Header-only) class, and make sure to inherit from the correct sensor type(s), eg `Thermometer`.

You'll need to implement any virtual methods, eg `getTemperature`, being sure to return data in the [SI units](https://en.wikipedia.org/wiki/International_System_of_Unit) required by the sensor type.

Try to follow the conventions used in existing sensor devices, take a look at [`BMP085.h`](https://github.com/loopj/i2c-sensor-hal/blob/master/src/BMP085.h) for a full example.

### Adding a New Sensor Type

If you'd like to add a new sensor type, for example you'd like to add an [Anemometer](https://en.wikipedia.org/wiki/Anemometer) to measure wind speed, you'll need to create a new class with virtual methods.

Make sure that your class defines a method which returns sensor results in [SI units](https://en.wikipedia.org/wiki/International_System_of_Units), eg meters per second.

Take a look at [`Accelerometer.h`](https://github.com/loopj/i2c-sensor-hal/blob/master/src/Accelerometer.h) for a full example.


### Adding a New Framework

Adding support for a new development framework is usually relatively simple. You'll need to implement the `readBytes`, `writeBytes` and `usleep` I2C functions in a new file named `I2CDevice_yourplatform.cpp`.

Make sure to wrap the implementation in framework-specific include guards, for example:

```c++
#ifdef ARDUINO
// Your code
#endif
```

Take a look at [`I2CDevice_arduino.cpp`](https://github.com/loopj/i2c-sensor-hal/blob/master/src/I2CDevice_arduino.cpp) for a full example.
