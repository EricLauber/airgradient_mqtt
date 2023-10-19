#include "FlashDataManager.h"

// Leverage EpoxyDuino to mock the onboard flash storage
#if defined(EPOXY_DUINO)
#define EEPROM EpoxyEepromEspInstance
#define FILE_SYSTEM fs::EpoxyFS
#else
#define FILE_SYSTEM LittleFS
#endif

namespace Data
{
    char FlashDataManager::ReadFromAddress(int address)
    {
        //return String(EEPROM.read(address));
        return EEPROM.read(address);
    }

    bool FlashDataManager::WriteToAddress(int address, char data)
    {
        EEPROM.write(address, data);
        return EEPROM.commit();
    }

    String FlashDataManager::ReadFromFile(String filename)
    {
        String fileContents;

        if (FILE_SYSTEM.exists(filename))
        {
            File file = FILE_SYSTEM.open(filename, "r");
            if (file)
            {
                while (file.available())
                {
                    fileContents += char(file.read());
                }
                file.close();
            }
            else
            {
                // todo - failure scenario
            }
        }
        else
        {
            // todo - failure scenario
        }

        return fileContents;
    }

    bool FlashDataManager::WriteToFile(String filename, DynamicJsonDocument json)
    {
        bool failed = false;

        File file = FILE_SYSTEM.open(filename, "w");
        if (file)
        {
            serializeJson(json, Serial);
            serializeJson(json, file);
            file.close();
        }
        else
        {
            // failure scenario
            failed = true;
        }
        
        return failed;
    }

    FlashDataManager::FlashDataManager()
    {
        EEPROM.begin(512);
        FILE_SYSTEM.begin();
    }
}