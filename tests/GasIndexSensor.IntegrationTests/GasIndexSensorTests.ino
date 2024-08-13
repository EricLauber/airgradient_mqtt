#line 2 "GasIndexSensorTests.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AUnitVerbose.h>
#include <SensirionGasIndexSensor.h>
#include <SensirionI2CSgp41.h>
#include <NOxGasIndexAlgorithm.h>
#include <VOCGasIndexAlgorithm.h>

using aunit::TestRunner;
using aunit::Verbosity;
using namespace IO;
using namespace IO::GasIndex;

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
