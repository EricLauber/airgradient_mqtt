#ifndef D1Mini_h
#define D1Mini_h

#include "../ISystem.h"
//#include "Esp.h"

using namespace Output;

namespace Output::ESP8266
{
    class D1Mini : public ISystem
    {
        public:
            // void Reset() override { ESP.reset(); };
            // void Restart() override { ESP.restart(); };
            void Reset() override {  };
            void Restart() override {  };
    };
}

#endif