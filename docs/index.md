# AirGradient for Arduino using MQTT

<img src="./assets/images/airgradient.png" align="right" width="200">

This is an Arduino software implementation for the AirGradient DIY Air Quality Sensor Pro, PCB version 4.2.

<br/><br/>
<img src="./assets/images/mqtt-logo.svg" align="right" width="200">

The base configuration for an AirGradient product is for it to log data to AirGradient's servers. This sketch augments that functionality with MQTT capabilities to log data to a server of your choice.

With this implementation you get:

- MQTT support with the option to continue using AirGradient's data logging.
- An object-oriented implementation that tries to follow SOLID to make it easier to extend.
- Automated test coverage built with [AUnit](https://github.com/bxparks/AUnit) and run using [EpoxyDuino](https://github.com/bxparks/EpoxyDuino) to simulate the behavior of real hardware and facilitate Continuous Integration.

<img src="./assets/images/diypro42kit.jpg" align="left" width="250">

AirGradient products are professional, accurate, long-lasting air quality monitors that are open-source and open-hardware. Through Arduino sketches like this one, you're free to upgrade your AirGradient's functionality and tweak it how you see fit.
