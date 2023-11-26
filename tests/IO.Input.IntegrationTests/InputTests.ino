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
    
    // Assert
    assertEqual(0.00, tvoc);
}

test(SensirionGasIndexSensorTests, GetNOX)
{
    // Arrange
    SensirionGasIndexSensor testGasIndexSensor = SensirionGasIndexSensor(Wire);
    testGasIndexSensor.SetCompenstation(37, .3);
    
    // Act
    float nox = testGasIndexSensor.GetNOXIndex();
    
    // Assert
    assertEqual(0.00, nox);
}   

// #include <Wire.h>

// test(ExampleSensor, SomeMethod)
// {
//     SensirionI2CSgp41 sgp41;

//     VOCGasIndexAlgorithm voc_algorithm;
//     NOxGasIndexAlgorithm nox_algorithm;

//     // time in seconds needed for NOx conditioning
//     uint16_t conditioning_s = 10;

//     sgp41.begin(Wire);



//     // this is the loop section



//     uint16_t error;
//     float humidity = 0;     // %RH
//     float temperature = 0;  // degreeC
//     uint16_t srawVoc = 0;
//     uint16_t srawNox = 0;
//     uint16_t defaultCompenstaionRh = 0x8000;  // in ticks as defined by SGP41
//     uint16_t defaultCompenstaionT = 0x6666;   // in ticks as defined by SGP41
//     uint16_t compensationRh = 0;              // in ticks as defined by SGP41
//     uint16_t compensationT = 0;               // in ticks as defined by SGP41

//     // 1. Sleep: Measure every second (1Hz), as defined by the Gas Index
//     // Algorithm
//     //    prerequisite
//     //delay(1000);

//     // 2. Measure temperature and humidity for SGP internal compensation
//     // error = sht4x.measureHighPrecision(temperature, humidity);
//     // if (error) {
//     //     Serial.print(
//     //         "SHT4x - Error trying to execute measureHighPrecision(): ");
//     //     errorToString(error, errorMessage, 256);
//     //     Serial.println(errorMessage);
//     //     Serial.println("Fallback to use default values for humidity and "
//     //                    "temperature compensation for SGP41");
//     //     compensationRh = defaultCompenstaionRh;
//     //     compensationT = defaultCompenstaionT;
//     // } else {
//     //     Serial.print("T:");
//     //     Serial.print(temperature);
//     //     Serial.print("\t");
//     //     Serial.print("RH:");
//     //     Serial.println(humidity);

//     //     // convert temperature and humidity to ticks as defined by SGP41
//     //     // interface
//     //     // NOTE: in case you read RH and T raw signals check out the
//     //     // ticks specification in the datasheet, as they can be different for
//     //     // different sensors
//         compensationT = static_cast<uint16_t>((temperature + 45) * 65535 / 175);
//         compensationRh = static_cast<uint16_t>(humidity * 65535 / 100);
//     // }

//     // 3. Measure SGP4x signals
//     if (conditioning_s > 0) {
//         // During NOx conditioning (10s) SRAW NOx will remain 0
//         error =
//             sgp41.executeConditioning(compensationRh, compensationT, srawVoc);
//         conditioning_s--;
//     } else {
//         error = sgp41.measureRawSignals(compensationRh, compensationT, srawVoc,
//                                         srawNox);
//     }

//     // 4. Process raw signals by Gas Index Algorithm to get the VOC and NOx
//     // index
//     //    values
//     if (error) {
//         Serial.print("SGP41 - Error trying to execute measureRawSignals(): ");
//         //errorToString(error, errorMessage, 256);
//         //Serial.println(errorMessage);
//     } else {
//         int32_t voc_index = voc_algorithm.process(srawVoc);
//         int32_t nox_index = nox_algorithm.process(srawNox);
//         Serial.print("VOC Index: ");
//         Serial.print(voc_index);
//         Serial.print("\t");
//         Serial.print("NOx Index: ");
//         Serial.println(nox_index);
//     }

//     assertTrue(true);
// }

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
