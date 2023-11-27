#ifndef Switchboard_h
#define Switchboard_h

// This header includes controls that adjust the behavior of the software on-build.


/*
    The Arduino IDE and components for ESP8266 will by default compile with the `fno-rtti` flag.

    This implementaton includes support for Run-time type information (RTTI) to be a bit more compliant with SOLID practices.
    To use this, adjust your compiler flags to use the `-frtti` flag instead. You can then adjust RTTI_ENABLED to 1.
    See the docs for more details.
*/
#define RTTI_ENABLED 0


// todo - alias the text for the <Library.h> rather that include them, so that referencing the Switchboard doesn't reference not-required includes
#if defined(EPOXY_DUINO)
// Leverage EpoxyDuino to mock the onboard flash storage
#include <EpoxyEepromEsp.h>
#include <EpoxyFS.h>
#define EEPROM EpoxyEepromEspInstance
#define FILE_SYSTEM fs::EpoxyFS

// EpoxyDuino serial
#define SOFTWARE_SERIAL_LIBRARY <StdioSerial.h>
#define SOFTWARE_SERIAL StdioSerial

// Reduce delays for test automation
#define CONFIG_DISPLAY_DELAY 1
#else
// Actual flash storage libraries
#include <EEPROM.h>
#include <LittleFS.h>
#define FILE_SYSTEM LittleFS

// Actual serial library
#define SOFTWARE_SERIAL_LIBRARY <SoftwareSerial.h>
#define SOFTWARE_SERIAL SoftwareSerial

// Actual delay to enable user to read display
#define CONFIG_DISPLAY_DELAY 500
#endif

#define BUTTON_TIMEOUT 4000

// Include functionality to facilitate debugging such as Serial.println() calls.
#define DEBUG_ENABLED 1

// Pin connected to AirGradient push button
#define BUTTON_PIN D7


#endif