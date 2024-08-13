#ifndef MockButton_h
#define MockButton_h

#include <IButton.h>

namespace IO
{
    class MockButton : public IButton
    {
        public:
            // Get button feedback for the pin. Option to set a maximum time in milliseconds to get input
            void UpdateButtonInput(int timeout = 0) override { };

            // Reset button status
            void Reset() override
            {
                this->SingleClicked = false;
                this->LongPressed = false;
            };
    };
}

#endif