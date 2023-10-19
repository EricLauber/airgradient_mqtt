#line 2 "FlashAndConfigTests.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <Data.h>

using aunit::TestRunner;
using aunit::Verbosity;
using namespace Data;

test(FlashDataManagerTests, Constructor)
{
    FlashDataManager* dataManager = new FlashDataManager();

    assertNotEqual(nullptr, dataManager);
}

test(FlashDataManagerTests, ReadWriteEEPROM)
{
    // Arrange
    FlashDataManager dataManager = FlashDataManager();

    int testAddress1 = 4;
    int testAddress2 = 10;
    char testData1 = 'A';
    char testData2 = 'Z';

    // Act
    dataManager.WriteToAddress(testAddress1, testData1);
    // Assert
    assertEqual(testData1, dataManager.ReadFromAddress(testAddress1));

    // Act
    dataManager.WriteToAddress(testAddress2, testData2);
    // Assert
    assertEqual(testData2, dataManager.ReadFromAddress(testAddress2));
}

test(FlashDataManagerTests, ReadWriteLitleFS)
{
    // Arrange
    FlashDataManager dataManager = FlashDataManager();

    String testFilename = "/myfile.json";
    
    DynamicJsonDocument testData1(1024);
    testData1["name"] = "Ash Ketchum";
    testData1["title"] = "Pokemon Master";
    String testData1AsString;
    serializeJson(testData1, testData1AsString);

    DynamicJsonDocument testData2(1024);
    testData2["name"] = "Gary Oak";
    testData2["title"] = "Viridian City Gym Leader";
    String testData2AsString;
    serializeJson(testData2, testData2AsString);
    
    // Act (create file and read from it)
    dataManager.WriteToFile(testFilename, testData1);
    // Assert
    //DynamicJsonDocument result1 = dataManager.ReadFromFile(testFilename);

    assertEqual(testData1AsString, dataManager.ReadFromFile(testFilename));

    // Act (overwrite file and read from it)
    dataManager.WriteToFile(testFilename, testData2);
    // Assert
    assertEqual(testData2AsString, dataManager.ReadFromFile(testFilename));
}

test(ConfigManagerTests, Constructor)
{
    ConfigManager* configManager = new ConfigManager();

    assertNotEqual(nullptr, configManager);
}

void setup()
{
#if ! defined(EPOXY_DUINO)
    delay(1000); // wait to prevent garbage on SERIAL_PORT_MONITOR
#endif
    SERIAL_PORT_MONITOR.begin(115200);
    while (!SERIAL_PORT_MONITOR); // needed for Leonardo/Micro

    TestRunner::setVerbosity(Verbosity::kAll);
}

void loop()
{
    TestRunner::run();
}
