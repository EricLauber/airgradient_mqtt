# See https://github.com/bxparks/EpoxyDuino for documentation about using
# EpoxyDuino to compile and run AUnit tests natively on Linux or MacOS.make run

include ../../.env

APP_NAME := DisplayTests
ARDUINO_LIBS := AUnit U8g2 Display Monochrome
ARDUINO_LIB_DIRS := \
	../../src \
	../../src/Display
include $(arduino_ide_dir)/libraries/EpoxyDuino/EpoxyDuino.mk