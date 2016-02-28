# Blynk Sensors Example App

Display sensor values on your iOS/Android device using [Blynk](http://www.blynk.cc/).

This example uses a ESP8266 device with a BMP085 sensor connected, but can easily be modified for other microcontrollers or sensors.

![Screenshot of Blynk app with Sensor data](http://i.imgur.com/YeAeTOH.png)

## Download the Blynk App

See Blynk's [getting started](http://www.blynk.cc/getting-started/) guide to download the Blynk app, and create a project with two charts (like the screenshot above).

## Install PlatformIO

```shell
python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)"
```

## Set your Blynk auth token in `main.ino`

```c++
// Blynk auth token (from the blynk app)
char blynkToken[] = "13efc9ffb16b40ae97f6b2f7726358be";

// WiFi access point credentials
char ssid[] = "my-wifi-network";
char password[] = "p455w0rd";
```

## Build and upload to ESP8266

```shell
$ platformio run -t upload
```
