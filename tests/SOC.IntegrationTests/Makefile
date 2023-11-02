# See https://github.com/bxparks/EpoxyDuino for documentation about using
# EpoxyDuino to compile and run AUnit tests natively on Linux or MacOS.make run

include ../../.env

APP_NAME := D1MiniTests
ARDUINO_LIBS := AUnit SOC Wemos
ARDUINO_LIB_DIRS := \
	../../src \
	../../src/SOC
EPOXY_CORE := EPOXY_CORE_ESP8266
include $(arduino_ide_dir)/libraries/EpoxyDuino/EpoxyDuino.mk