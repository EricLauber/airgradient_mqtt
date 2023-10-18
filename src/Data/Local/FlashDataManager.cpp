#include "FlashDataManager.h"

// Leverage EpoxyDuino to mock the onboard flash storage
#if defined(EPOXY_DUINO)
#define EEPROM EpoxyEepromEspInstance
#define FILE_SYSTEM fs::EpoxyFS
#else
#define FILE_SYSTEM LittleFS
#endif

namespace Data::Local
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

    // std::map<String, String> FlashDataManager::ReadServerConfiguration()
    // {
    //     std::map<String, String> configuration;

    //     if (FILE_SYSTEM.exists(filename))
    //     {
    //         File configFile = FILE_SYSTEM.open(filename, "r");
    //         if (configFile)
    //         {
    //             String configData;
    //             while (configFile.available())
    //             {
    //                 configData += char(configFile.read());
    //             }
    //             DynamicJsonDocument json(1024);
    //             auto deserializeError = deserializeJson(json, configData);
    //             serializeJson(json, Serial);
    //             if (!deserializeError)
    //             {	
    //                 // todo
    //                 // this is specific to mqtt. maybe find a way to loop through everything and provide a big map?
    //                 configuration.emplace("server", json["mqtt_server"]);
    //                 configuration.emplace("username", json["mqtt_user"]);
    //                 configuration.emplace("password", json["mqtt_pass"]);
    //                 configuration.emplace("topic", json["mqtt_topic"]);
    //             }
    //             else
    //             {
    //                 // todo - failure scenario
    //             }
    //             configFile.close();
    //         }
    //         else
    //         {
    //             // todo - failure scenario
    //         }
    //     }
    //     else
    //     {
    //         // todo - failure scenario
    //     }

    //     return configuration;
    // }
}