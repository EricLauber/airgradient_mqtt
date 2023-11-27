#line 2 "CO2SensorTests.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AUnitVerbose.h>
#include <IO.h>
#include <SenseairCO2Sensor.h>

using aunit::TestRunner;
using aunit::Verbosity;
using namespace IO;
using namespace IO::CO2;

test(SenseairCO2SensorTests, Constructor)
{
    // Arrange, Act
    ICO2Sensor *testCO2Sensor = new SenseairCO2Sensor();

    // Assert
    assertNotEqual(nullptr, testCO2Sensor);
}

test(SenseairCO2SensorTests, GetCO2Raw)
{
    // Arrange, Act
    SenseairCO2Sensor testCO2Sensor = SenseairCO2Sensor();

    int co2 = testCO2Sensor.GetCO2Raw();
    
    // Assert - in EpoxyDuino without real hardware, timeout should return -3
    assertEqual(-3, co2);
}

test(SenseairCO2SensorTests, GetAverageCO2)
{
    // Arrange, Act
    SenseairCO2Sensor testCO2Sensor = SenseairCO2Sensor();

    int co2 = testCO2Sensor.GetAverageCO2(5);
    
    // Assert - in EpoxyDuino without real hardware, collection failuer should return -5
    assertEqual(-5, co2);
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
