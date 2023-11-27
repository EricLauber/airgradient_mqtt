# See https://github.com/bxparks/EpoxyDuino for documentation about using
# EpoxyDuino to compile and run AUnit tests natively on Linux or MacOS.make run

include ../../.env

APP_NAME := ButtonTests
ARDUINO_LIBS := AUnit IO Input EpoxyEepromEsp EpoxyFS
ARDUINO_LIB_DIRS := \
	../../src \
	../../src/IO
include $(arduino_ide_dir)/libraries/EpoxyDuino/EpoxyDuino.mk