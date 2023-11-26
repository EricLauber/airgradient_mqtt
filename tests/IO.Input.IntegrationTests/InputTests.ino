#line 2 "InputTests.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AUnitVerbose.h>
#include <IO.h>
#include "TimeControlButton.h"

// should this break out to its own test file?
#include <SensirionHTSensor.h>
#include <WString.h>

// should this break out to its own test file?
#include <SensirionGasIndexSensor.h>
#include <SensirionI2CSgp41.h>
#include <NOxGasIndexAlgorithm.h>
#include <VOCGasIndexAlgorithm.h>



using aunit::TestRunner;
using aunit::Verbosity;
using namespace IO;
using namespace IO::Input;

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
    testButton->SetCurrentMillis(0);
    testButton->ReadButtonData();

    // Loop 1
    testButton->SetCurrentMillis(100);
    // press the button
    digitalReadValue(BUTTON_PIN, 0);
    testButton->ReadButtonData();

    // Loop 2
    testButton->SetCurrentMillis(1300);
    // release the button
    digitalReadValue(BUTTON_PIN, 1);
    testButton->ReadButtonData();

    // Assert
    assertTrue(testButton->SingleClicked);
    assertFalse(testButton->LongPressed);
}

test(TimeControlButtonTests, MillisecondControl)
{
    TimeControlButton *testButton = new TimeControlButton(BUTTON_PIN);
    unsigned long testMillisValue = 0;

    testButton->SetCurrentMillis(testMillisValue);
    assertEqual(testMillisValue, testButton->GetCurrentMillis());

    testMillisValue = 100;
    testButton->SetCurrentMillis(testMillisValue);
    assertEqual(testMillisValue, testButton->GetCurrentMillis());

    testMillisValue = 500;
    testButton->SetCurrentMillis(testMillisValue);
    assertEqual(testMillisValue, testButton->GetCurrentMillis());

    testMillisValue = 1000;
    testButton->SetCurrentMillis(testMillisValue);
    assertEqual(testMillisValue, testButton->GetCurrentMillis());

    testMillisValue = 3000;
    testButton->SetCurrentMillis(testMillisValue);
    assertEqual(testMillisValue, testButton->GetCurrentMillis());
    
    testMillisValue = 5000;
    testButton->SetCurrentMillis(testMillisValue);
    assertEqual(testMillisValue, testButton->GetCurrentMillis());
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
    testButton->SetCurrentMillis(0);
    testButton->ReadButtonData();

    // Loop 1
    testButton->SetCurrentMillis(100);
    // press the button
    digitalReadValue(BUTTON_PIN, 0);
    testButton->ReadButtonData();

    // Loop 2
    testButton->SetCurrentMillis(3000);
    testButton->ReadButtonData();

    // Loop 3
    testButton->SetCurrentMillis(5000);
    // release the button
    digitalReadValue(BUTTON_PIN, 1);
    testButton->ReadButtonData();

    // Assert
    assertFalse(testButton->SingleClicked);
    assertTrue(testButton->LongPressed);
}

test(SensirionHTSensorTests, Constructor)
{
    // Arrange, Act
    IHTSensor *testHTSensor = new SensirionHTSensor();

    // Assert
    assertNotEqual(nullptr, testHTSensor);
}

test(SensirionHTSensorTests, GetHumidity)
{
    // Arrange
    SensirionHTSensor testHTSensor = SensirionHTSensor();
    
    // Act
    float humidity = testHTSensor.GetHumidity();
    String humidityString = String(humidity);

    // Assert
    assertEqual(" nan", humidityString);
}   

test(SensirionHTSensorTests, GetTemperature)
{
    // Arrange
    SensirionHTSensor testHTSensor = SensirionHTSensor();
    
    // Act
    float temperature = testHTSensor.GetTemperature();
    String temperatureString = String(temperature);

    // Assert
    assertEqual(" nan", temperatureString);
} 

test(SensirionGasIndexSensorTests, Constructor)
{
    // Arrange, Act
    IGasIndexSensor *testGasIndexSensor = new SensirionGasIndexSensor(Wire);

    // Assert
    assertNotEqual(nullptr, testGasIndexSensor);
}

test(SensirionGasIndexSensorTests, GetTVOC)
{
    // Arrange
    SensirionGasIndexSensor testGasIndexSensor = SensirionGasIndexSensor(Wire);
    testGasIndexSensor.SetCompenstation(37, .3);
    
    // Act
    float tvoc = testGasIndexSensor.GetTVOCIndex();
    String tvocString = String(tvoc);

    // Assert
    assertEqual(" nan", tvocString);
}   

void setup()
{
#if ! defined(EPOXY_DUINO)
    delay(1000); // wait to prevent garbage on SERIAL_PORT_MONITOR
#endif
    SERIAL_PORT_MONITOR.begin(115200);
    while (!SERIAL_PORT_MONITOR); // needed for Leonardo/Micro

    //TestRunner::setVerbosity(Verbosity::kAll);
}

void loop()
{
    TestRunner::run();
}
