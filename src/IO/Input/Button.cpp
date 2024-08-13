#include "Button.h"

namespace IO::Input
{
    Button::Button(int pin)
    {
        this->buttonPin = pin;
        pinMode(pin, INPUT_PULLUP);
    }

    // Get button feedback for the pin. Option to set a maximum time in milliseconds to get input
    void Button::UpdateButtonInput(int timeout)
    {
        SetupInitialLoopValues();

        while (!this->SingleClicked && !this->LongPressed)
        {
            ReadButtonData();

            // If a max-wait is configured, break out if we've exceeded that length of time
            if ((timeout > 0) && (timeout <= (loopStartTime + GetCurrentMillis())))
                break;
                
            delay(100);
        }
    }

    void Button::SetupInitialLoopValues()
    {
        pressedTime = 0;
        releasedTime = 0;
        lastButtonState = LOW;
        isPressing = false;
        loopStartTime = GetCurrentMillis();
    }

    void Button::ReadButtonData()
    {
        // Pull-up resistor means a press will read as LOW - toggle to make it more intuitive
        int buttonState = !digitalRead(buttonPin);

        // Button is pressed
        if (lastButtonState == LOW && buttonState == HIGH)
        {
            pressedTime = GetCurrentMillis();
            isPressing = true;
        }

        // Button is released - could be a single click
        else if (lastButtonState == HIGH && buttonState == LOW)
        {
            isPressing = false;
            releasedTime = GetCurrentMillis();
            long pressDuration = releasedTime - pressedTime;
            if (pressDuration < shortpresstime)
            {
                this->SingleClicked = true;
            }
        }

        if (isPressing)
        {
            long pressedDuration = GetCurrentMillis() - pressedTime;
            if (pressedDuration > longpresstime)
            {
                this->LongPressed = true;
            }
        }

        lastButtonState = buttonState;
    }

    // Reset button status
    void Button::Reset()
    {
        this->SingleClicked = false;
        this->LongPressed = false;
    }
}



