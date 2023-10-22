#ifndef System_h
#define System_h

#include "../ISystem.h"

namespace Output::ESP
{
    class ESP8266 : public ISystem
    {
        public:
            void Reset() override { ESP.reset(); };
            void Restart() override { ESP.restart(); };
    };
}
#endif