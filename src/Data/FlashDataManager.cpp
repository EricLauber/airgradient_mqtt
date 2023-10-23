#include "FlashDataManager.h"

namespace Data
{
    char FlashDataManager::ReadFromAddress(int address)
    {
        //return String(EEPROM.read(address));
        return EEPROM.read(address);
    }

    bool FlashDataManager::WriteToAddress(int address, char data)
    {
        // EEPROM returns true on success.
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
                // on failure, do not set string
            }
        }
        else
        {
            // on failure, do not set string
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

    // todo - write tests to prove behavior when file exists or doesn't exist
    bool FlashDataManager::DeleteFile(String filename)
    {
        if (FILE_SYSTEM.exists(filename))
        {
            // LittleFS returns true if there was a file to remove.
            return FILE_SYSTEM.remove(filename);
        }
        else
        {
            // Operation succeeded in an intended way.
            return true;
        }
    }

    FlashDataManager::FlashDataManager()
    {
        EEPROM.begin(512);
        FILE_SYSTEM.begin();
    }
}