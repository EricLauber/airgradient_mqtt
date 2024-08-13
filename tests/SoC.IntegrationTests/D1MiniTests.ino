#line 2 "D1MiniTests.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AUnitVerbose.h>
#include <IO.h>
#include <D1Mini.h>

using aunit::TestRunner;
using aunit::Verbosity;
using namespace IO;
using namespace IO::Wemos;

test(D1MiniTests, Constructor)
{
    ISoC *testSoC = new D1Mini();

    assertNotEqual(nullptr, testSoC);
}

test(D1MiniTests, GetChipID)
{
    ISoC *testSoC = new D1Mini();

    assertEqual(0, testSoC->GetChipID());
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
