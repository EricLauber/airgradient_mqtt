#ifndef MockSystem_h
#define MockSystem_h

#include "ISystem.h"

namespace Output
{
    class MockSystem : public ISystem
    {
        public:
            bool ResetCalled = false;
            bool RestartCalled = false;

            // todo - should these return something for test purposes? even if in real life they never would.
            void Reset() override { ResetCalled = true; };
            void Restart() override { RestartCalled = true; };

            // Clear Status
            void Clear()
            {
                ResetCalled = false;
                RestartCalled = false;
            }

    };
}

#endif