#line 2 "InputTests.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AUnitVerbose.h>
#include <Input.h>
#include "TimeControlButton.h"

using aunit::TestRunner;
using aunit::Verbosity;
using namespace Input;
// TODO namespace not implemented yet

#define BUTTON_PIN D7

test(ButtonTests, Constructor)
{
    IButton *testButton = new Button(BUTTON_PIN);

    assertNotEqual(nullptr, testButton);
}

test(ButtonTests, Reset)
{
    IButton *testButton = new Button(BUTTON_PIN);

    testButton->SingleClicked = true;
    testButton->LongPressed = true;
    testButton->Reset();

    assertFalse(testButton->SingleClicked);
    assertFalse(testButton->LongPressed);
}

// todo - variables need public access to confirm operation
// test(ButtonTests, SetupInitialLoopValues)
// {
//     IButton *testButton = new Button(BUTTON_PIN);

    
// }

test(TimeControlMockButtonTests, Constructor)
{
    IButton *testButton = new TimeControlButton(BUTTON_PIN);

    assertNotEqual(nullptr, testButton);
}

test(TimeControlButtonTests, ShortPress)
{
    // Arrange
    int shortPressMaxTime = 2500; //todo - find a better way to handle this number
    TimeControlButton *testButton = new TimeControlButton(BUTTON_PIN);
    // AirGradient uses a Pull-up resistor and button grounds it out. High is 'false'
    digitalReadValue(BUTTON_PIN, 1);
    testButton->SetupInitialLoopValues();

    // Act

    // Loop 0
    testButton->setCurrentMillis(0);
    testButton->ReadButtonData();

    // Loop 1
    testButton->setCurrentMillis(100);
    // press the button
    digitalReadValue(BUTTON_PIN, 0);
    testButton->ReadButtonData();

    // Loop 2
    testButton->setCurrentMillis(1300);
    // release the button
    digitalReadValue(BUTTON_PIN, 1);
    testButton->ReadButtonData();

    // Assert
    assertTrue(testButton->SingleClicked);
    assertFalse(testButton->LongPressed);
}

test(TimeControlButtonTests, LongPress)
{
    // Arrange
    int shortPressMaxTime = 2500; //todo - find a better way to handle this number
    TimeControlButton *testButton = new TimeControlButton(BUTTON_PIN);
    // AirGradient uses a Pull-up resistor and button grounds it out. High is 'false'
    digitalReadValue(BUTTON_PIN, 1);
    testButton->SetupInitialLoopValues();

    // Act

    // Loop 0
    Serial.println("loop 0");
    testButton->setCurrentMillis(0);
    testButton->ReadButtonData();

    // Loop 1
    Serial.println("loop 1");
    testButton->setCurrentMillis(100);
    // press the button
    digitalReadValue(BUTTON_PIN, 0);
    testButton->ReadButtonData();

    // Loop 1
    Serial.println("loop 2");
    testButton->setCurrentMillis(2500);
    // press the button
    digitalReadValue(BUTTON_PIN, 0);
    testButton->ReadButtonData();

    // Loop 2
    Serial.println("loop 3");
    testButton->setCurrentMillis(5000);
    // release the button
    digitalReadValue(BUTTON_PIN, 1);
    testButton->ReadButtonData();

    // Assert
    assertFalse(testButton->SingleClicked);
    assertTrue(testButton->LongPressed);
}

void setup()
{
#if ! defined(EPOXY_DUINO)
    delay(1000); // wait to prevent garbage on SERIAL_PORT_MONITOR
#endif
    SERIAL_PORT_MONITOR.begin(115200);
    while (!SERIAL_PORT_MONITOR); // needed for Leonardo/Micro

    TestRunner::setVerbosity(Verbosity::kAll);
}

void loop()
{
    TestRunner::run();
}
