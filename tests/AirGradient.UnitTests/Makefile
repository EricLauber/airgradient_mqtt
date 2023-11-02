# See https://github.com/bxparks/EpoxyDuino for documentation about using
# EpoxyDuino to compile and run AUnit tests natively on Linux or MacOS.make run

include ../../.env

APP_NAME := AirGradientTests
ARDUINO_LIBS := AUnit EpoxyEepromEsp EpoxyFS EPOXY_CORE_ESP8266 ArduinoJson AirGradient StateMachine Display Input SOC Data 
ARDUINO_LIB_DIRS := \
	../../src
include $(arduino_ide_dir)/libraries/EpoxyDuino/EpoxyDuino.mk