#line 2 "FlashAndConfigTests.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <Data.h>
#include <WString.h>

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

test(FlashDataManagerTests, DeleteLitleFS)
{
    // Arrange
    FlashDataManager dataManager = FlashDataManager();

    String testFilename = "/myfile.json";
    
    DynamicJsonDocument testData1(1024);
    testData1["name"] = "Ash Ketchum";
    testData1["title"] = "Pokemon Master";
    String testData1AsString;
    serializeJson(testData1, testData1AsString);
    // Create file to delete
    dataManager.WriteToFile(testFilename, testData1);

    // Act
    bool result = dataManager.DeleteFile(testFilename);
    
    // Assert - LittleFS returns true on success
    assertTrue(result);
    assertEqual("", dataManager.ReadFromFile(testFilename));
}

test(ConfigManagerTests, Constructor)
{
    ConfigManager* configManager = new ConfigManager();

    assertNotEqual(nullptr, configManager);
}

test(ConfigManagerTests, ClearData)
{
    // Arrange
    ConfigManager configManager = ConfigManager();

    // Act
    bool result = configManager.ClearData();

    // Assert
    assertTrue(result);
}

test(ConfigManagerTests, ReadWriteDisplayConfiguration)
{
    // Arrange
    ConfigManager configManager = ConfigManager();

    // Act and Assert
    assertTrue(configManager.WriteDisplayConfigurationMode(DisplayConfiguration::TempCμgm3));
    // Assert
    assertEqual((int)DisplayConfiguration::TempCμgm3, (int)configManager.ReadDisplayConfigurationMode());

    // Act
    assertTrue(configManager.WriteDisplayConfigurationMode(DisplayConfiguration::TempFμgm3));
    // Assert
    assertEqual((int)DisplayConfiguration::TempFμgm3, (int)configManager.ReadDisplayConfigurationMode());

    // Act
    assertTrue(configManager.WriteDisplayConfigurationMode(DisplayConfiguration::TempCAQI));
    // Assert
    assertEqual((int)DisplayConfiguration::TempCAQI, (int)configManager.ReadDisplayConfigurationMode());

    // Act
    assertTrue(configManager.WriteDisplayConfigurationMode(DisplayConfiguration::TempFAQI));
    // Assert
    assertEqual((int)DisplayConfiguration::TempFAQI, (int)configManager.ReadDisplayConfigurationMode());
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
