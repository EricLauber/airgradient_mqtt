#ifndef MockSoC_h
#define MockSoC_h

#include "ISoC.h"

namespace IO
{
    class MockSoC : public ISoC
    {
        public:
            bool ResetCalled = false;
            bool RestartCalled = false;

            // todo - should these return something for test purposes? even if in real life they never would.
            void Reset() override { ResetCalled = true; };
            void Restart() override { RestartCalled = true; };
            int GetChipID() override { return 16777215; };

            // Clear Status
            void Clear()
            {
                ResetCalled = false;
                RestartCalled = false;
            }

    };
}

#endif