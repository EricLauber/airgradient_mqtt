#ifndef D1Mini_h
#define D1Mini_h

#include "../ISoC.h"

using namespace IO;

namespace IO::Wemos
{
    class D1Mini : public ISoC
    {
        public:
            void Reset() override { ESP.reset(); };
            void Restart() override { ESP.restart(); };
            int GetChipID() override { return ESP.getChipId(); };
    };
}

#endif