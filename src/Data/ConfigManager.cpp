#include "ConfigManager.h"

namespace Data
{
    ConfigManager::ConfigManager()
    {
        dataManager = FlashDataManager();
    }

    int ConfigManager::ReadDisplayConfigurationMode()
    {
        return 0;
    }

    bool ConfigManager::WriteDisplayConfigurationMode(int mode)
    {
        return false;
    }


    std::map<String, String> ConfigManager::ReadServerConfiguration(NetworkProtocol protocol)
    {
        std::map<String, String> configuration;

        DynamicJsonDocument json(1024);
        //todo - mqtt file and web api file
        String thisIsTheJson = dataManager.ReadFromFile("/config.json");

        // auto deserializeError = deserializeJson(json, configData);
        // serializeJson(json, Serial);
        // if (!deserializeError)
        // {	
        //     // todo
        //     // this is specific to mqtt. maybe find a way to loop through everything and provide a big map?
        //     configuration.emplace("server", json["mqtt_server"]);
        //     configuration.emplace("username", json["mqtt_user"]);
        //     configuration.emplace("password", json["mqtt_pass"]);
        //     configuration.emplace("topic", json["mqtt_topic"]);
        // }

        return configuration;
    }

    int ConfigManager::WriteServerConfiguration(std::map<String, String> configuration, NetworkProtocol protocol)
    {
        return 0;
    }
}

