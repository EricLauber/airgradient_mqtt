#line 2 "AirGradientTests.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AUnitVerbose.h>
#include <AirGradientPro.h>
#include "../Mocks/MockDisplay.h"
#include "../Mocks/MockButton.h"
#include "../Mocks/MockSystem.h"

using aunit::TestRunner;
using aunit::Verbosity;


test(AirGradientTests, Constructor)
{
    IDisplay *mockDisplay = new MockDisplay();
    IButton *mockButton = new MockButton();
    ISystem *mockSystem = new MockSystem();

    AirGradientPro *airGradient = new AirGradientPro(mockDisplay, mockButton, mockSystem);

    assertNotEqual(nullptr, airGradient);
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
