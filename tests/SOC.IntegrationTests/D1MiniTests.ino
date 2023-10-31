#line 2 "D1MiniTests.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AUnitVerbose.h>
#include <Output.h>
#include <D1Mini.h>

using aunit::TestRunner;
using aunit::Verbosity;
using namespace Output;
using namespace Output::ESP8266;

test(D1MiniTests, Constructor)
{
    ISystem *testSystem = new D1Mini();

    assertNotEqual(nullptr, testSystem);
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
