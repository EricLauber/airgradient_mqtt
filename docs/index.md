# AirGradient for Arduino using MQTT

<img src="./assets/images/airgradient.png" align="right" width="200">

This is an Arduino software implementation for the AirGradient DIY Air Quality Sensor Pro, PCB version 4.2. I have paused development for this project.

I created this fork of [AirGradient's Arduino code](https://github.com/airgradienthq/arduino) prior to their implementation of MQTT and local web server support. My intention was to add that functionality while also bringing in other software development best practices such as automated testing and Continuous Integration and patterns like SOLID. [Click here for detailed documentation about the implementation](https://ericlauber.github.io/airgradient_mqtt/).

The previous base configuration for an AirGradient product is for it to log data to AirGradient's servers. This sketch augments that functionality with MQTT capabilities to log data to a server of your choice.

With this implementation you get:

- MQTT support with the option to continue using AirGradient's data logging.
- An object-oriented implementation that tries to follow SOLID to make it easier to extend.
- Automated test coverage built with [AUnit](https://github.com/bxparks/AUnit) and run using [EpoxyDuino](https://github.com/bxparks/EpoxyDuino) to simulate the behavior of real hardware and facilitate continuous integration.
- Example implementations using GitHub Actions to Continuous Integrate and run tests based on EpoxyDuino.
- Example documentation built with MkDocs.
