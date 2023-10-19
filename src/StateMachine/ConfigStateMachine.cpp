#include "ConfigStateMachine.h"
#include "TypeConversionFunctions.h"
//#include "Arduino.h"

// Pin connected to AirGradient push button
#define BUTTON_PIN D7
//#define RTTI_ENABLED 1

using namespace Display;
using namespace Input;
using namespace Data;
namespace TypeCast = StateMachineTypeConversionFunctions;

ConfigStateMachine::ConfigStateMachine(IDisplay* display, IButton* button) : MachineBase(MachineType::CONFIG)
{
    this->display = display;
    this->button = button;
    configManager = ConfigManager();
    
    // This is the default/starting state
    StateBase *newState = new SelectState();
    this->SetState(*newState);
}

void ConfigStateMachine::Run()
{
    // 1. Take inputs

    // idea - could the length of this timeout be based around the current state? no timeout for some states...
    button->UpdateButtonInput(4000);

    // 2. Pass inputs to State
    if (button->LongPressed)
    {
        state->LongPress(this);
        button->Reset();
    }
    else if (button->SingleClicked)
    {;
        state->ShortPress(this);
        button->Reset();
    }


    // 3. If a state transition occurs, take action based on the transition
}

int ConfigStateMachine::WriteToDisplay(String line1, String line2, String line3)
{
    return display->WriteLines(line1, line2, line3);
}

void ConfigStateMachine::SetDisplayConfiguration(DisplayConfiguration displayConfiguration)
{
    this->selectedConfiguration = displayConfiguration;
}

DisplayConfiguration ConfigStateMachine::GetDisplayConfiguration()
{
    return selectedConfiguration;
}

//todo - test coverage (at least for saving the data)
void ConfigStateMachine::SaveDisplayConfiguration()
{
    WriteToDisplay(
        OLEDStrings::ConfigSavingLine1,
        OLEDStrings::ConfigSavingLine2,
        OLEDStrings::ConfigSavingLine3
    );

    // true on success
    bool result = configManager.WriteDisplayConfigurationMode(selectedConfiguration);

    delay(500);

    if (result)
    {
        WriteToDisplay(
            OLEDStrings::ConfigSavedSuccessLine1,
            OLEDStrings::ConfigSavedSuccessLine2,
            OLEDStrings::ConfigSavedSuccessLine3
        );
    }
    else
    {
        WriteToDisplay(
            OLEDStrings::ConfigSavedFailedLine1,
            OLEDStrings::ConfigSavedFailedLine2,
            OLEDStrings::ConfigSavedFailedLine3
        );
    }

    delay(500);

    SetState(SelectState::GetInstance());
}

#pragma region State_Press_Functions

// SelectState short-press rotates to the EditConfigState
void SelectState::ShortPress(MachineBase* machine)
{
    machine->SetState(EditConfigState::GetInstance());
}

// SelectState long-press has the same action as the short-press
void SelectState::LongPress(MachineBase* machine)
{
    machine->SetState(EditConfigState::GetInstance());
}

// EditConfigState short-press rotates to the ClearState
void EditConfigState::ShortPress(MachineBase* machine)
{
    machine->SetState(ClearState::GetInstance());
}

// EditConfigState long-press switches to the DisplayConfig states
void EditConfigState::LongPress(MachineBase* machine)
{
    machine->SetState(DisplayConfigTempCμgm3::GetInstance());
}

// ClearState short-press rotates to the RebootState
void ClearState::ShortPress(MachineBase* machine)
{
    //setState(machine, new RebootState());
    machine->SetState(RebootState::GetInstance());
}

//void ClearState::LongPress(MachineBase &machine)
void ClearState::LongPress(MachineBase* machine)
{
    
}

// RebootState short-press rotates back to the EditConfigState
void RebootState::ShortPress(MachineBase* machine)
{
    //setState(machine, new EditConfigState());
    machine->SetState(EditConfigState::GetInstance());
}

//void RebootState::LongPress(MachineBase &machine)
void RebootState::LongPress(MachineBase* machine)
{
    // build a wrapper around this call
    //ESP.restart();
}




// DisplayConfigTempCμgm3 short-press rotates to the DisplayConfigTempFμgm3
void DisplayConfigTempCμgm3::ShortPress(MachineBase* machine)
{
    machine->SetState(DisplayConfigTempFμgm3::GetInstance());
}


void DisplayConfigTempCμgm3::LongPress(MachineBase* machine)
{
    if (ConfigStateMachine *configMachine = TypeCast::machineCast<ConfigStateMachine *>(machine))
    {
        configMachine->SaveDisplayConfiguration();
    }
}

// DisplayConfigTempFμgm3 short-press rotates to the DisplayConfigTempCAQI
void DisplayConfigTempFμgm3::ShortPress(MachineBase* machine)
{
    machine->SetState(DisplayConfigTempCAQI::GetInstance());
}

void DisplayConfigTempFμgm3::LongPress(MachineBase* machine)
{
    if (ConfigStateMachine *configMachine = TypeCast::machineCast<ConfigStateMachine *>(machine))
    {
        configMachine->SaveDisplayConfiguration();
    }
}

// DisplayConfigTempCAQI short-press rotates to the DisplayConfigTempFAQI
void DisplayConfigTempCAQI::ShortPress(MachineBase* machine)
{
    machine->SetState(DisplayConfigTempFAQI::GetInstance());
}

void DisplayConfigTempCAQI::LongPress(MachineBase* machine)
{
    if (ConfigStateMachine *configMachine = TypeCast::machineCast<ConfigStateMachine *>(machine))
    {
        configMachine->SaveDisplayConfiguration();
    }
}

// DisplayConfigTempFAQI short-press rotates back to the DisplayConfigTempCμgm3
void DisplayConfigTempFAQI::ShortPress(MachineBase* machine)
{
    machine->SetState(DisplayConfigTempCμgm3::GetInstance());
}

void DisplayConfigTempFAQI::LongPress(MachineBase* machine)
{
    if (ConfigStateMachine *configMachine = TypeCast::machineCast<ConfigStateMachine *>(machine))
    {
        configMachine->SaveDisplayConfiguration();
    }
}

#pragma endregion State_Press_Functions

#pragma region State_GetInstance_Functions

StateBase& SelectState::GetInstance()
{
    static SelectState singleton;
    return singleton;
}

StateBase& EditConfigState::GetInstance()
{
    static EditConfigState singleton;
    return singleton;
}

StateBase& ClearState::GetInstance()
{
    static ClearState singleton;
    return singleton;
}

StateBase& RebootState::GetInstance()
{
    static RebootState singleton;
    return singleton;
}

StateBase& DisplayConfigTempCμgm3::GetInstance()
{
    static DisplayConfigTempCμgm3 singleton;
    return singleton;
}

StateBase& DisplayConfigTempFμgm3::GetInstance()
{
    static DisplayConfigTempFμgm3 singleton;
    return singleton;
}

StateBase& DisplayConfigTempCAQI::GetInstance()
{
    static DisplayConfigTempCAQI singleton;
    return singleton;
}

StateBase& DisplayConfigTempFAQI::GetInstance()
{
    static DisplayConfigTempFAQI singleton;
    return singleton;
}

#pragma endregion State_GetInstance_Functions

#pragma region State_Enter_Functions

void SelectState::Enter(MachineBase* machine) 
{
#if RTTI_ENABLED
    //Serial.println("RTTI enabled");
    if(ConfigStateMachine* configMachine = dynamic_cast<ConfigStateMachine*>(machine))
    {
        configMachine->WriteToDisplay(
            OLEDStrings::SelectStateLine1,
            OLEDStrings::SelectStateLine2,
            OLEDStrings::SelectStateLine3
        );
    }
#else
    //Serial.println("RTTI disabled");
    if (ConfigStateMachine *configMachine = TypeCast::machineCast<ConfigStateMachine *>(machine))
    {
        configMachine->WriteToDisplay(
            OLEDStrings::SelectStateLine1,
            OLEDStrings::SelectStateLine2,
            OLEDStrings::SelectStateLine3
        );
    }
#endif    
}


void EditConfigState::Enter(MachineBase* machine) 
{
#if RTTI_ENABLED
    if (ConfigStateMachine* configMachine = dynamic_cast<ConfigStateMachine*>(machine))
    {
        configMachine->WriteToDisplay(
            OLEDStrings::EditConfigStateLine1,
            OLEDStrings::EditConfigStateLine2,
            OLEDStrings::EditConfigStateLine3
        );
    }
#else
    if (ConfigStateMachine *configMachine = TypeCast::machineCast<ConfigStateMachine *>(machine))
    {
        configMachine->WriteToDisplay(
            OLEDStrings::EditConfigStateLine1,
            OLEDStrings::EditConfigStateLine2,
            OLEDStrings::EditConfigStateLine3
        );
    }
#endif    
}

void ClearState::Enter(MachineBase* machine) 
{
#if RTTI_ENABLED
    if (ConfigStateMachine* configMachine = dynamic_cast<ConfigStateMachine*>(machine))
    {
        configMachine->WriteToDisplay(
            OLEDStrings::ClearConfigStateLine1,
            OLEDStrings::ClearConfigStateLine2,
            OLEDStrings::ClearConfigStateLine3
        );
    }
#else
    if (ConfigStateMachine *configMachine = TypeCast::machineCast<ConfigStateMachine *>(machine))
    {
        configMachine->WriteToDisplay(
            OLEDStrings::ClearConfigStateLine1,
            OLEDStrings::ClearConfigStateLine2,
            OLEDStrings::ClearConfigStateLine3
        );
    }
#endif    
}
void RebootState::Enter(MachineBase* machine) 
{
#if RTTI_ENABLED
    if (ConfigStateMachine* configMachine = dynamic_cast<ConfigStateMachine*>(machine))
    {
        configMachine->WriteToDisplay(
            OLEDStrings::RebootStateLine1,
            OLEDStrings::RebootStateLine2,
            OLEDStrings::RebootStateLine3
        );
    }
#else
    if (ConfigStateMachine *configMachine = TypeCast::machineCast<ConfigStateMachine *>(machine))
    {
        configMachine->WriteToDisplay(
            OLEDStrings::RebootStateLine1,
            OLEDStrings::RebootStateLine2,
            OLEDStrings::RebootStateLine3
        );
    }
#endif    
}

void DisplayConfigTempCμgm3::Enter(MachineBase* machine) 
{
    if (ConfigStateMachine *configMachine = TypeCast::machineCast<ConfigStateMachine *>(machine))
    {
        configMachine->WriteToDisplay(
            OLEDStrings::ConfigTempC,
            OLEDStrings::ConfigPMμgm3,
            OLEDStrings::ConfigSaveMessage
        );
        configMachine->SetDisplayConfiguration(DisplayConfiguration::TempCμgm3);
    }
}

void DisplayConfigTempFμgm3::Enter(MachineBase* machine) 
{
    if (ConfigStateMachine *configMachine = TypeCast::machineCast<ConfigStateMachine *>(machine))
    {
        configMachine->WriteToDisplay(
            OLEDStrings::ConfigTempF,
            OLEDStrings::ConfigPMμgm3,
            OLEDStrings::ConfigSaveMessage
        );
        configMachine->SetDisplayConfiguration(DisplayConfiguration::TempFμgm3);
    }  
}

void DisplayConfigTempCAQI::Enter(MachineBase* machine) 
{
    if (ConfigStateMachine *configMachine = TypeCast::machineCast<ConfigStateMachine *>(machine))
    {
        configMachine->WriteToDisplay(
            OLEDStrings::ConfigTempC,
            OLEDStrings::ConfigPMAQI,
            OLEDStrings::ConfigSaveMessage
        );
        configMachine->SetDisplayConfiguration(DisplayConfiguration::TempCAQI);
    }  
}

void DisplayConfigTempFAQI::Enter(MachineBase* machine) 
{
    if (ConfigStateMachine *configMachine = TypeCast::machineCast<ConfigStateMachine *>(machine))
    {
        configMachine->WriteToDisplay(
            OLEDStrings::ConfigTempF,
            OLEDStrings::ConfigPMAQI,
            OLEDStrings::ConfigSaveMessage
        );
        configMachine->SetDisplayConfiguration(DisplayConfiguration::TempFAQI);
    }  
}
#pragma endregion State_Enter_Functions

#pragma region State_Exit_Functions

void SelectState::Exit(MachineBase* machine) {}
void EditConfigState::Exit(MachineBase* machine) {}
void ClearState::Exit(MachineBase* machine) {}
void RebootState::Exit(MachineBase* machine) {}

void DisplayConfigTempCμgm3::Exit(MachineBase* machine) {}
void DisplayConfigTempFμgm3::Exit(MachineBase* machine) {}
void DisplayConfigTempCAQI::Exit(MachineBase* machine) {}
void DisplayConfigTempFAQI::Exit(MachineBase* machine) {}

#pragma endregion State_Exit_Functions