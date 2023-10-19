#ifndef FlashDataManager_h
#define FlashDataManager_h

#include <ArduinoJson.h>
#include <WString.h>

// Leverage EpoxyDuino to mock the onboard flash storage
#if defined(EPOXY_DUINO)
#include <EpoxyEepromEsp.h>
#include <EpoxyFS.h>
#else
#include <EEPROM.h>
#include <LittleFS.h>
#endif

namespace Data
{
    class FlashDataManager
    {
        public:
            char ReadFromAddress(int address);
            bool WriteToAddress(int address, char data);
            String ReadFromFile(String filename);
            bool WriteToFile(String filename, DynamicJsonDocument json);

            FlashDataManager();
    };
}

#endif