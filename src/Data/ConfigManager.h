#ifndef ConfigManager_h
#define ConfigManager_h

#include <WString.h>
#include <map>
#include "NetworkProtocol.h"
#include "./Local/IFlashDataManager.h"

using namespace Data::Local;

namespace Data
{
    // This interface provides communication with data storage.
    class ConfigManager
    {
        private:
            IFlashDataManager* dataManager;

        public:
            int ReadDisplayConfigurationMode();
            bool WriteDisplayConfigurationMode(int mode);
            std::map<String, String> ReadServerConfiguration(NetworkProtocol protocol);
            int WriteServerConfiguration(std::map<String, String> configuration, NetworkProtocol protocol);

            ConfigManager(IFlashDataManager* dataManager);
    };
}

#endif