# AirGradient MQTT for Arduino

<img src="./docs/assets/images/airgradient.png" align="right" width="200">

This is an Arduino software implementation for the AirGradient DIY Air Quality Sensor Pro, PCB version 4.2.

The base configuration for an AirGradient product is for it to log data to AirGradient's servers. This sketch augments that functionality with MQTT capabilities to log data to a server of your choice.

I've developed this software to be object oriented. I've applied several modern programming practices such as SOLID and automated testing to a degree that I thought made sense. [Click here for detailed documentation about the implementation](https://ericlauber.github.io/airgradient_mqtt/).

## Getting Started and uploading this sketch

1. Download and Install the [Arduino IDE](https://www.arduino.cc/en/software), [Arduino CLI](https://arduino.github.io/arduino-cli/0.19/installation/), or [VS Code](https://code.visualstudio.com/) with the [Arduino extension](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino) to your system.
1. Clone this repo or download the latest release (a zip of the source code).
1. Open `airgradient_mqtt.ino` with your chosen Arduino tools.
1. Install all required Arduino reference libraries.
1. Plug in the microcontroller for your AirGradient (such as an ESP8266 Wemos LOLIN D1 mini) and upload the sketch to the controller.
