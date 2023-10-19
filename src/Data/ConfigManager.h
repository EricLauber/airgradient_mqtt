#ifndef ConfigManager_h
#define ConfigManager_h

#include <WString.h>
#include <map>
#include "NetworkProtocol.h"
#include "DisplayConfiguration.h"
#include "FlashDataManager.h"

namespace Data
{
    // This interface provides communication with data storage.
    class ConfigManager
    {
        private:
            FlashDataManager dataManager;
            int address = 4;

        public:
            DisplayConfiguration ReadDisplayConfigurationMode();
            bool WriteDisplayConfigurationMode(DisplayConfiguration mode);
            std::map<String, String> ReadServerConfiguration(NetworkProtocol protocol);
            int WriteServerConfiguration(std::map<String, String> configuration, NetworkProtocol protocol);

            ConfigManager();
    };
}

#endif