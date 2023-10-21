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


// Leverage EpoxyDuino to mock the onboard flash storage
#if defined(EPOXY_DUINO)
#define EEPROM EpoxyEepromEspInstance
#define FILE_SYSTEM fs::EpoxyFS
#else
#define FILE_SYSTEM LittleFS
#endif

// Include functionality to facilitate debugging such as Serial.println() calls.
#define DEBUG_ENABLED 0

#endif