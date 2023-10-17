#ifndef Button_h
#define Button_h

#include "IButton.h"
#include "Arduino.h"

namespace Input
{
    class Button : public IButton
    {
        private:
            int buttonPin = 0;
            unsigned long pressedTime = 0;
            unsigned long releasedTime = 0;

            int shortpresstime = 2500;
            int longpresstime = 2500;

            int lastButtonState = LOW;
            bool isPressing = false;

            int loopStartTime = 0;

        public:
            Button(int pin);

            // Get button feedback for the pin. Option to set a maximum time in milliseconds to get input
            void UpdateButtonInput(int timeout) override;
            // Reset button status
            void Reset() override;

            void SetupInitialLoopValues();
            void ReadButtonData();

        // Wrapper around hardware millis() call to enable mocking
        protected:
            virtual unsigned long getCurrentMillis() const { return ::millis(); }
    };
}
#endif