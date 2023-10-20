#line 2 "StateMachineTests.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AUnitVerbose.h>
#include <StateMachine.h>
#include "MockDisplay.h"
#include "MockButton.h"

using aunit::TestRunner;
using aunit::Verbosity;
// TODO namespace not implemented yet
//using namespace StateMachine;

test(StateMachineTests, Constructor_and_State_Transitions)
{
    IDisplay *mockDisplay = new MockDisplay();
    IButton *mockButton = new MockButton();
    MachineBase *testMachine = new ConfigStateMachine(mockDisplay, mockButton);

    assertNotEqual(nullptr, testMachine);

    // ConfigStateMachines should begin with the SelectState.
    bool correctInitialState = false;
    if (dynamic_cast<SelectState*>(testMachine->GetState()) != nullptr)
    {
        correctInitialState = true;
    }
    assertTrue(correctInitialState);

    // Main State Selection

    // todo - for future readability, break these out into separate tests that leverage a test fixture and each configure the previous, expected state
    //https://github.com/bxparks/AUnit/tree/develop#test-fixtures
    bool enteredEditConfigState = false;
    testMachine->GetState()->ShortPress(testMachine);
    if (dynamic_cast<EditConfigState*>(testMachine->GetState()) != nullptr)
    {
        enteredEditConfigState = true;
    }
    assertTrue(enteredEditConfigState);

    bool enteredClearState = false;
    testMachine->GetState()->ShortPress(testMachine);
    if (dynamic_cast<ClearState*>(testMachine->GetState()) != nullptr)
    {
        enteredClearState = true;
    }
    assertTrue(enteredClearState);

    bool enteredRebootState = false;
    testMachine->GetState()->ShortPress(testMachine);
    if (dynamic_cast<RebootState*>(testMachine->GetState()) != nullptr)
    {
        enteredRebootState = true;
    }
    assertTrue(enteredRebootState);

    bool loopedBackToEditState = false;
    testMachine->GetState()->ShortPress(testMachine);
    if (dynamic_cast<EditConfigState*>(testMachine->GetState()) != nullptr)
    {
        loopedBackToEditState = true;
    }
    assertTrue(loopedBackToEditState);

    // Configuration Mode Selection
    bool enteredTempCμgm3 = false;
    testMachine->GetState()->LongPress(testMachine);
    if (dynamic_cast<DisplayConfigTempCμgm3*>(testMachine->GetState()) != nullptr)
    {
        enteredTempCμgm3 = true;
    }
    assertTrue(enteredTempCμgm3);

    // Rotate through Configuration Mode states
    bool enteredTempFμgm3 = false;
    testMachine->GetState()->ShortPress(testMachine);
    if (dynamic_cast<DisplayConfigTempFμgm3*>(testMachine->GetState()) != nullptr)
    {
        enteredTempFμgm3 = true;
    }
    assertTrue(enteredTempFμgm3);

    bool enteredTempCAQI = false;
    testMachine->GetState()->ShortPress(testMachine);
    if (dynamic_cast<DisplayConfigTempCAQI*>(testMachine->GetState()) != nullptr)
    {
        enteredTempCAQI = true;
    }
    assertTrue(enteredTempCAQI);

    bool enteredTempFAQI = false;
    testMachine->GetState()->ShortPress(testMachine);
    if (dynamic_cast<DisplayConfigTempFAQI*>(testMachine->GetState()) != nullptr)
    {
        enteredTempFAQI = true;
    }
    assertTrue(enteredTempFAQI);

    bool loopedBackToTempCμgm3 = false;
    testMachine->GetState()->ShortPress(testMachine);
    if (dynamic_cast<DisplayConfigTempCμgm3*>(testMachine->GetState()) != nullptr)
    {
        loopedBackToTempCμgm3 = true;
    }
    assertTrue(loopedBackToTempCμgm3);
}

test(StateMachineTests, GetSetDisplayConfig)
{
    // Arrange
    IDisplay *mockDisplay = new MockDisplay();
    IButton *mockButton = new MockButton();
    ConfigStateMachine *testMachine = new ConfigStateMachine(mockDisplay, mockButton);

    // Act
    testMachine->SetDisplayConfiguration(DisplayConfiguration::TempCAQI);
    // Assert
    assertEqual((int)DisplayConfiguration::TempCAQI, (int)testMachine->GetDisplayConfiguration());

    // Act
    testMachine->SetDisplayConfiguration(DisplayConfiguration::TempFAQI);
    // Assert
    assertEqual((int)DisplayConfiguration::TempFAQI, (int)testMachine->GetDisplayConfiguration());

    // Act
    testMachine->SetDisplayConfiguration(DisplayConfiguration::TempCμgm3);
    // Assert
    assertEqual((int)DisplayConfiguration::TempCμgm3, (int)testMachine->GetDisplayConfiguration());

    // Act
    testMachine->SetDisplayConfiguration(DisplayConfiguration::TempFμgm3);
    // Assert
    assertEqual((int)DisplayConfiguration::TempFμgm3, (int)testMachine->GetDisplayConfiguration());
}

test(StateMachineTests, DisplayConfigLongPress)
{
    // Arrange
    IDisplay *mockDisplay = new MockDisplay();
    IButton *mockButton = new MockButton();
    ConfigStateMachine *testMachine = new ConfigStateMachine(mockDisplay, mockButton);
    ConfigManager configManager = ConfigManager();
    
    // Act
    testMachine->SetState(DisplayConfigTempCμgm3::GetInstance());
    testMachine->GetState()->LongPress(testMachine);
    // Assert
    assertEqual((int)DisplayConfiguration::TempCμgm3, (int)configManager.ReadDisplayConfigurationMode());

    // Act
    testMachine->SetState(DisplayConfigTempFμgm3::GetInstance());
    testMachine->GetState()->LongPress(testMachine);
    // Assert
    assertEqual((int)DisplayConfiguration::TempFμgm3, (int)configManager.ReadDisplayConfigurationMode());

    // Act
    testMachine->SetState(DisplayConfigTempCAQI::GetInstance());
    testMachine->GetState()->LongPress(testMachine);
    // Assert
    assertEqual((int)DisplayConfiguration::TempCAQI, (int)configManager.ReadDisplayConfigurationMode());

    // Act
    testMachine->SetState(DisplayConfigTempFAQI::GetInstance());
    testMachine->GetState()->LongPress(testMachine);
    // Assert
    assertEqual((int)DisplayConfiguration::TempFAQI, (int)configManager.ReadDisplayConfigurationMode());

}

test(StateMachineTests, RunMachine)
{
    // Arrange
    IDisplay *mockDisplay = new MockDisplay();
    IButton *mockButton = new MockButton();
    MachineBase *testMachine = new ConfigStateMachine(mockDisplay, mockButton);

    // ConfigStateMachines should begin with the SelectState.
    bool correctInitialState = false;
    if (dynamic_cast<SelectState*>(testMachine->GetState()) != nullptr)
    {
        correctInitialState = true;
    }
    assertTrue(correctInitialState);

    mockButton->SingleClicked = true;

    // Act
    testMachine->Run();

    // Assert

    // todo - for future readability, break these out into separate tests that leverage a test fixture and each configure the previous, expected state
    //https://github.com/bxparks/AUnit/tree/develop#test-fixtures
    bool enteredEditConfigState = false;
    if (dynamic_cast<EditConfigState*>(testMachine->GetState()) != nullptr)
    {
        enteredEditConfigState = true;
    }
    assertTrue(enteredEditConfigState);

    // The final step of machine.run is to reset the button state.
    assertFalse(mockButton->SingleClicked);
    assertFalse(mockButton->LongPressed);
}

test(StateMachineTests, Machine_WriteToDisplay)
{
    // Arrange
    MockDisplay *mockDisplay = new MockDisplay();
    IButton *mockButton = new MockButton();
    ConfigStateMachine *testMachine = new ConfigStateMachine(mockDisplay, mockButton);

    String testLine1 = "Hello";
    String testLine2 = "Goodbye";
    String testLine3 = "See you later";

    // Act
    testMachine->WriteToDisplay(testLine1, testLine2, testLine3);

    // Assert
    assertEqual(testLine1, mockDisplay->Line1);
    assertEqual(testLine2, mockDisplay->Line2);
    assertEqual(testLine3, mockDisplay->Line3);
}

test(StateMachineTests, State_WriteToDisplay)
{
    // Arrange
    MockDisplay *mockDisplay = new MockDisplay();
    IButton *mockButton = new MockButton();

    // Main selection states

    // Act - ConfigStateMachine should begin with the SelectState.
    MachineBase *testMachine = new ConfigStateMachine(mockDisplay, mockButton);

    // Assert
    assertEqual(OLEDStrings::SelectStateLine1, mockDisplay->Line1);
    assertEqual(OLEDStrings::SelectStateLine2, mockDisplay->Line2);
    assertEqual(OLEDStrings::SelectStateLine3, mockDisplay->Line3);

    // Act - EditConfigState
    testMachine->GetState()->ShortPress(testMachine);

    // Assert
    assertEqual(OLEDStrings::EditConfigStateLine1, mockDisplay->Line1);
    assertEqual(OLEDStrings::EditConfigStateLine2, mockDisplay->Line2);
    assertEqual(OLEDStrings::EditConfigStateLine3, mockDisplay->Line3);

    // Act - ClearConfigState
    testMachine->GetState()->ShortPress(testMachine);

    // Assert
    assertEqual(OLEDStrings::ClearConfigStateLine1, mockDisplay->Line1);
    assertEqual(OLEDStrings::ClearConfigStateLine2, mockDisplay->Line2);
    assertEqual(OLEDStrings::ClearConfigStateLine3, mockDisplay->Line3);

    // Act - RebootState
    testMachine->GetState()->ShortPress(testMachine);

    // Assert
    assertEqual(OLEDStrings::RebootStateLine1, mockDisplay->Line1);
    assertEqual(OLEDStrings::RebootStateLine2, mockDisplay->Line2);
    assertEqual(OLEDStrings::RebootStateLine3, mockDisplay->Line3);

    // Act - EditConfigState
    testMachine->GetState()->ShortPress(testMachine);

    // Assert
    assertEqual(OLEDStrings::EditConfigStateLine1, mockDisplay->Line1);
    assertEqual(OLEDStrings::EditConfigStateLine2, mockDisplay->Line2);
    assertEqual(OLEDStrings::EditConfigStateLine3, mockDisplay->Line3);


    // DisplayConfig States


    // Act - DisplayConfigTempCμgm3
    testMachine->GetState()->LongPress(testMachine);

    // Assert
    assertEqual(OLEDStrings::ConfigTempC, mockDisplay->Line1);
    assertEqual(OLEDStrings::ConfigPMμgm3, mockDisplay->Line2);
    assertEqual(OLEDStrings::ConfigSaveMessage, mockDisplay->Line3);

    // Act - DisplayConfigTempFμgm3
    testMachine->GetState()->ShortPress(testMachine);

    // Assert
    assertEqual(OLEDStrings::ConfigTempF, mockDisplay->Line1);
    assertEqual(OLEDStrings::ConfigPMμgm3, mockDisplay->Line2);
    assertEqual(OLEDStrings::ConfigSaveMessage, mockDisplay->Line3);

    // Act - DisplayConfigTempCAQI
    testMachine->GetState()->ShortPress(testMachine);

    // Assert
    assertEqual(OLEDStrings::ConfigTempC, mockDisplay->Line1);
    assertEqual(OLEDStrings::ConfigPMAQI, mockDisplay->Line2);
    assertEqual(OLEDStrings::ConfigSaveMessage, mockDisplay->Line3);

    // Act - DisplayConfigTempFAQI
    testMachine->GetState()->ShortPress(testMachine);

    // Assert
    assertEqual(OLEDStrings::ConfigTempF, mockDisplay->Line1);
    assertEqual(OLEDStrings::ConfigPMAQI, mockDisplay->Line2);
    assertEqual(OLEDStrings::ConfigSaveMessage, mockDisplay->Line3);

    // Act - DisplayConfigTempCμgm3
    testMachine->GetState()->ShortPress(testMachine);

    // Assert
    assertEqual(OLEDStrings::ConfigTempC, mockDisplay->Line1);
    assertEqual(OLEDStrings::ConfigPMμgm3, mockDisplay->Line2);
    assertEqual(OLEDStrings::ConfigSaveMessage, mockDisplay->Line3);
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
