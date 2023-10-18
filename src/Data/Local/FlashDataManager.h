#ifndef FlashDataManager_h
#define FlashDataManager_h

#include <IFlashDataManager.h>

// Leverage EpoxyDuino to mock the onboard flash storage
#if defined(EPOXY_DUINO)
#include <EpoxyEepromEsp.h>
#include <EpoxyFS.h>
#else
#include <EEPROM.h>
#include <LittleFS.h>
#endif

namespace Data::Local
{
    class FlashDataManager : public IFlashDataManager
    {
        public:
            char ReadFromAddress(int address) override;
            bool WriteToAddress(int address, char data) override;
            String ReadFromFile(String filename) override;
            bool WriteToFile(String filename, DynamicJsonDocument json) override;

            FlashDataManager();
    };
}

#endif