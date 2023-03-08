# HomeSensorIno

```shell
arduino-cli core install arduino:avr

arduino-cli lib install "DHT sensor library"
arduino-cli lib install ArduinoJson

# MH-Z19 by Jonathan Dempsey
arduino-cli lib install MH-Z19

sudo apt install screen
```

## License

The source code of this program is dual-licensed under MIT License and LGPL-3.0.

When statically linking this program to [WifWaf/MH-Z19](https://github.com/WifWaf/MH-Z19), you need to apply LGPL-3.0 to the object code because the library is licensed under LGPL-3.0.
