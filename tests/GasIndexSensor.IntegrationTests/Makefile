# See https://github.com/bxparks/EpoxyDuino for documentation about using
# EpoxyDuino to compile and run AUnit tests natively on Linux or MacOS.make run

include ../../.env

APP_NAME := GasIndexSensorTests
ARDUINO_LIBS := AUnit IO GasIndex Sensirion_Core Sensirion_I2C_Sgp41 Sensirion_Gas_Index_Algorithm
ARDUINO_LIB_DIRS := \
	../../src \
	../../src/IO
include $(arduino_ide_dir)/libraries/EpoxyDuino/EpoxyDuino.mk