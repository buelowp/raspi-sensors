# Raspi-sensor
Nodejs C++ plugin, allowing to easily read data from raspberryPi's sensors.

## Supported sensors
For now, those sensors are supported :
- DHT22(or DHT21) (GPIO)
- DHT11 (GPIO)
- PIR (GPIO)
- BMP180 (i2c)
- TLS2561 (i2c)

## Requirement
C++ implementation for most Linux based dev boards
- Onion Omega2
- More to come

### i2c sensors
To use **i2c** sensors, the i2c driver should be loaded, usually using [raspi-config](https://learn.adafruit.com/adafruits-raspberry-pi-lesson-4-gpio-setup/configuring-i2c). The file (usually `/dev/i2c-1`) used to communicate with the bus will be asked during the installation.

### GPIO sensors
If you wish to use **GPIO** sensors, an existing installation of [wiringPi](http://wiringpi.com/pins/) is required. The shared library of **wiringPi** should be generated, and present in the default location, i.e. `/usr/local/lib`.

### Compiling
```
mkdir build
cd build
cmake ..
```

## Sensors types and returned values
| Sensor name   | Sensor type | Value type      |
| ------------- | ----------- | --------------- |
| TSL2561       | TSL2561     | Light intensity |
| BMP180        | BMP180      | Temperature     |
|               |             | Pressure        |
| DHT22/21/11   | DHT22/21/11 | Temperature     |
|               |             | Humidity        |
| PIR Motion Sensor | PIR     | Boolean         |

| Value type      | Value unit     | Value unit display |
| --------------- | -------------- | ------------------ |
| Light intensity | Lux            | Lux                |
| Temperature     | Celsius Degree | °C                 |
| Pressure        | Pascal         | Pa                 |
| Humidity        | Percent        | %                  |
| Boolean         | Boolean        | Boolean            |

## Example

## Note
Note that, for now, root credentials are needed for any GPIO sensors because **wiringPi** needs it to access the GPIO bus, and because we need to access the i2c located in `/dev`.

## Disclaimer
May not work super well for a while
