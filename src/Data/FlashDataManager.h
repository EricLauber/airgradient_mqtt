#ifndef FlashDataManager_h
#define FlashDataManager_h

#include <ArduinoJson.h>
#include <WString.h>
#include "../Switchboard.h"

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