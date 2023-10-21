# Integrating with Home Assistant

Home Assistant is a free and open-source software for home automation that is designed to be the central control system for smart home devices with focus on local control and privacy.

My goal behind adding MQTT to the AirGradient was to integrate with Home Assistant and use HA as an MQTT Broker. [Follow these instructions to configure Home Assistant in this way](https://www.home-assistant.io/integrations/mqtt).

## General HA setup

1. Create a user for mqtt.
1. Setup the broker. Configure it for the user.
1. Point the publisher or subscriber to the broker (in our case the AirGradient is an MQTT publisher). Has to be able to call mqtt:// instead of http:// and access the port.
    1. If you have custom firewall or routing rules in place, you may run into some challenges. I wasn't able to use DNS and nginx Proxy Manager to provide a friendly hostname for AirGradient to use, and instead had to use Home Assistant's IP address in order to establish a connection.
1. Add sensors to the yaml in home assistant to receive and parse the data based on the MQTT topic.
1. Update the UI to visualize the data.

## Creating sensors within Home Assistant

I created the following sensors in `configuration.yaml` while using the topic `home/roomname`. You'll need to modify the code to match your intended topic.

```yaml
# Air Gradient sensors
mqtt:
  - sensor:
      name: "Room-name Temperature"
      state_topic: "home/roomname/temperature"
      unit_of_measurement: "°F"
  - sensor:
      name: "Room-name Humidity"
      state_topic: "home/roomname/humidity"
      unit_of_measurement: "%"
  - sensor:
      name: "Room-name NOX Index"
      state_topic: "home/roomname/nox_index"
  - sensor:
      name: "Room-name TVOC Index"
      state_topic: "home/roomname/tvoc_index"
  - sensor:
      name: "Room-name PM 1"
      state_topic: "home/roomname/pm01"
      unit_of_measurement: "µg/m3"
  - sensor:
      name: "Room-name PM 2.5"
      state_topic: "home/roomname/pm25"
      unit_of_measurement: "µg/m3"
  - sensor:
      name: "Room-name AQI"
      state_topic: "home/roomname/pm25AQI"
  - sensor:
      name: "Room-name PM 0.3"
      state_topic: "home/roomname/pm03"
      unit_of_measurement: "µg/m3"
  - sensor:
      name: "Room-name PM 10"
      state_topic: "home/roomname/pm10"
      unit_of_measurement: "µg/m3"
  - sensor:
      name: "Room-name CO2"
      state_topic: "home/roomname/co2"
      unit_of_measurement: "ppm"
```

## Visualization

Here are two sample visualizations I build for Home Assistant. TODO - add screenshots.

AQI Gauge Card

```yaml
type: gauge
entity: sensor.room-name_aqi
name: Air Quality Index
needle: true
min: 0
max: 250
segments:
  - from: 0
    color: '#43a047'
  - from: 51
    color: '#ffa600'
  - from: 101
    color: '#f68f1e'
  - from: 151
    color: '#ed1c25'
  - from: 201
    color: '#a2064a'
```

Metrics List

```yaml
type: entities
entities:
  - entity: sensor.room-name_temperature
    name: Temperature
  - entity: sensor.room-name_humidity
    name: Humidity
  - entity: sensor.room-name_co2
    name: CO2
  - entity: sensor.room-name_pm_0_3
    name: PM 0.3
  - entity: sensor.room-name_pm_1
    name: PM 1
  - entity: sensor.room-name_pm_2_5
    name: PM 2.5
  - entity: sensor.room-name_pm_10
    name: PM 10
  - entity: sensor.room-name_aqi
    name: Air Quality Index
  - entity: sensor.room-name_nox_index
    name: NOX Index
  - entity: sensor.room-name_tvoc_index
    name: TVOC Index
title: room-name Air Quality

```
