#line 2 "HTSensorTests.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AUnitVerbose.h>
#include <IO.h>
#include <SensirionHTSensor.h>
#include <WString.h>

using aunit::TestRunner;
using aunit::Verbosity;
using namespace IO;
using namespace IO::HT;

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
