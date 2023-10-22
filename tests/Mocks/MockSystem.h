#ifndef MockSystem_h
#define MockSystem_h

#include <Arduino.h>
#include "ISystem.h"

namespace Output
{
    class MockSystem : public ISystem
    {
        public:
            // todo - should these return something for test purposes? even if in real life they never would.
            void Reset() override { Serial.println("Reset called."); };
            void Restart() override { Serial.println("Restart called."); };
    };
}

#endif