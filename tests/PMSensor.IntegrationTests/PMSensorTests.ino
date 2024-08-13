#line 2 "PMSensorTests.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AUnitVerbose.h>
#include <IO.h>
#include <PlantowerPMSensor.h>

using aunit::TestRunner;
using aunit::Verbosity;
using namespace IO;
using namespace IO::PM;

test(PlantowerPMSensorTests, Constructor)
{
    // Arrange, Act
    IPMSensor *testPMSensor = new PlantowerPMSensor();

    // Assert
    assertNotEqual(nullptr, testPMSensor);
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
