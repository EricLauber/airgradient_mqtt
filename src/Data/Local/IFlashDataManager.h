#ifndef IFlashDataManager_h
#define IFlashDataManager_h

#include <ArduinoJson.h>
#include <WString.h>

namespace Data::Local
{
    class IFlashDataManager
    {
        public:
            virtual char ReadFromAddress(int address) = 0;
            virtual bool WriteToAddress(int address, char data) = 0;
            virtual String ReadFromFile(String filename) = 0;
            virtual bool WriteToFile(String filename, DynamicJsonDocument json) = 0;
    };
}

#endif