#ifndef D1Mini_h
#define D1Mini_h

#include "../ISystem.h"

// todo - change Output to something like SOC and ESP8266/blah namespace to Wemos or something to that effect
using namespace Output;

namespace Output::blah
{
    class D1Mini : public ISystem
    {
        public:

// EpoxyDuino does not currently support these functions.
#if defined(EPOXY_DUINO)
            void Reset() override {  };
            void Restart() override {  };
#else
            void Reset() override { ESP.reset(); };
            void Restart() override { ESP.restart(); };
#endif
    };
}

#endif