#ifndef D1Mini_h
#define D1Mini_h

#include "../ISOC.h"
#include <ESP.h>

// todo - change Output to something like SOC and ESP8266/blah namespace to Wemos or something to that effect
using namespace SOC;

namespace SOC::Wemos
{
    class D1Mini : public ISOC
    {
        public:
            void Reset() override { ESP.reset(); };
            void Restart() override { ESP.restart(); };
            int GetChipID() override { return ESP.getChipId(); };
    };
}

#endif