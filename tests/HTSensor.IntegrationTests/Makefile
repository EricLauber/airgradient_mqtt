# See https://github.com/bxparks/EpoxyDuino for documentation about using
# EpoxyDuino to compile and run AUnit tests natively on Linux or MacOS.make run

include ../../.env

APP_NAME := HTSensorTests
ARDUINO_LIBS := AUnit IO HT arduino-sht SensirionHTSensor
ARDUINO_LIB_DIRS := \
	../../src \
	../../src/IO
include $(arduino_ide_dir)/libraries/EpoxyDuino/EpoxyDuino.mk