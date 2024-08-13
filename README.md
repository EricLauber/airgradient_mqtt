# AirGradient for Arduino with Automated Tests

<img src="./docs/assets/images/airgradient.png" align="right" width="200">

This is an Arduino software implementation for the AirGradient DIY Air Quality Sensor Pro, PCB version 4.2. I have paused development for this project.

I created this fork of [AirGradient's Arduino code](https://github.com/airgradienthq/arduino) prior to their implementation of MQTT and local web server support. My intention was to add that functionality while also bringing in other software development best practices such as automated testing and Continuous Integration and patterns like SOLID. [Click here for detailed documentation about the implementation](https://ericlauber.github.io/airgradient_mqtt/).

Please feel free to use this project as an example of applying modern software development best practices to Arduino projects.

## Getting Started and uploading this sketch

1. Download and Install the [Arduino IDE](https://www.arduino.cc/en/software), [Arduino CLI](https://arduino.github.io/arduino-cli/0.19/installation/), or [VS Code](https://code.visualstudio.com/) with the [Arduino extension](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino) to your system.
1. Clone this repo or download the latest release (a zip of the source code).
1. Open `airgradient_mqtt.ino` with your chosen Arduino tools.
1. Install all required Arduino reference libraries.
1. Plug in the microcontroller for your AirGradient (such as an ESP8266 Wemos LOLIN D1 mini) and upload the sketch to the controller.
