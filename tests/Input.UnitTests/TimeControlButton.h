#ifndef TimeControlButton_h
#define TimeControlButton_h

#include "Button.h"

namespace Input
{
    // Inherits the Button object so we can mock Arduino behavior and test Button functions
    class TimeControlButton : public Button
    {
        public:
            unsigned long GetCurrentMillis() const override { return mMillis; }
            void SetCurrentMillis(unsigned long ms) { mMillis = ms; }
            TimeControlButton(int timeout = 0) : Button(timeout) { };
        private:
            unsigned long mMillis;
    };
}

#endif