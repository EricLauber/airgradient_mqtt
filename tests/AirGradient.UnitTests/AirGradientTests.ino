#line 2 "AirGradientTests.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AUnitVerbose.h>
#include <AirGradientPro.h>
#include "../Mocks/Mocks.h"

using aunit::TestRunner;
using aunit::Verbosity;


test(AirGradientTests, Constructor)
{
    IDisplay *mockDisplay = new MockDisplay();
    IButton *mockButton = new MockButton();
    ISoC *mockSoC = new MockSoC();
    IHTSensor *mockHTSensor = new MockHTSensor();

    AirGradientPro *airGradient = new AirGradientPro(mockDisplay, mockButton, mockSoC, mockHTSensor);
    assertNotEqual(nullptr, airGradient);
}

test(AirGradientTests, Startup)
{
    IDisplay *mockDisplay = new MockDisplay();
    IButton *mockButton = new MockButton();
    ISoC *mockSoC = new MockSoC();
    IHTSensor *mockHTSensor = new MockHTSensor();

    AirGradientPro airGradient = AirGradientPro(mockDisplay, mockButton, mockSoC, mockHTSensor);
    
    airGradient.Startup();
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
