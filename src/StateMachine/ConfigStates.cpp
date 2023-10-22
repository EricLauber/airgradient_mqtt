#include "ConfigStateMachine.h"

// todo - wrap around RTTI switchboard directive
#include "TypeConversionFunctions.h"
// todo - wrap around RTTI switchboard directive
namespace TypeCast = StateMachineTypeConversionFunctions;

#pragma region State_Press_Functions

#pragma region Main_States

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

void ClearState::LongPress(MachineBase* machine)
{
    //todo - call the functions that clear the local config and filesystem
}

// RebootState short-press rotates back to the EditConfigState
void RebootState::ShortPress(MachineBase* machine)
{
    //setState(machine, new EditConfigState());
    machine->SetState(EditConfigState::GetInstance());
}

void RebootState::LongPress(MachineBase* machine)
{
    if (ConfigStateMachine *configMachine = TypeCast::machineCast<ConfigStateMachine *>(machine))
    {
        configMachine->Restart();
    }
}

#pragma endregion Main_States

#pragma region Config_States


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

#pragma endregion Config_States

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