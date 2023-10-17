#include "Arduino.h"
#include "Button.h"

namespace Input
{
    Button::Button(int pin)
    {
        this->buttonPin = pin;
        pinMode(pin, INPUT_PULLUP);
    }

    // Get button feedback for the pin. Option to set a maximum time in milliseconds to get input
    void Button::UpdateButtonInput(int timeout = 0)
    {
        SetupInitialLoopValues();

        while (!this->SingleClicked && !this->LongPressed)
        {
            ReadButtonData();

            // If a max-wait is configured, break out if we've exceeded that length of time
            if ((timeout > 0) && (timeout <= (loopStartTime + getCurrentMillis())))
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
        loopStartTime = getCurrentMillis();
    }

    void Button::ReadButtonData()
    {
        Serial.println("pressedTime: " + String(pressedTime));
        Serial.println("releasedTime: " + String(releasedTime));


        Serial.println("reading button data");
        // Pull-up resistor means a press will read as LOW - toggle to make it more intuitive
        int buttonState = !digitalRead(buttonPin);

        // Button is pressed
        if (lastButtonState == LOW && buttonState == HIGH)
        {
            Serial.println("Button has been pressed!");
            pressedTime = getCurrentMillis();
            isPressing = true;
        }

        // Button is released - could be a single click
        else if (lastButtonState == HIGH && buttonState == LOW)
        {
            Serial.println("button was released");
            isPressing = false;
            releasedTime = getCurrentMillis();
            long pressDuration = releasedTime - pressedTime;
            if (pressDuration < shortpresstime)
            {
                Serial.println("it is a single click");
                this->SingleClicked = true;
            }
        }

        if (isPressing)
        {
            Serial.println("button still being pressed");
            long pressedDuration = getCurrentMillis() - pressedTime;
            if (pressedDuration > longpresstime)
            {
                Serial.println("hit the point that this is a long press");
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



