#include "ConfigStateMachine.h"

using namespace Display;
using namespace Input;
using namespace Output;
using namespace Data;

ConfigStateMachine::ConfigStateMachine(IDisplay* display, IButton* button, ISystem* system) : MachineBase(MachineType::CONFIG)
{
    this->display = display;
    this->button = button;
    this->system = system;
    configManager = ConfigManager();
    
    // This is the default/starting state
    StateBase *newState = new SelectState();
    this->SetState(*newState);
}

void ConfigStateMachine::Run()
{
    // 1. Take inputs

    // idea - could the length of this timeout be based around the current state? no timeout for some states...
    button->UpdateButtonInput(BUTTON_TIMEOUT);

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

// todo - tie delay to configurable constant.
void ConfigStateMachine::SaveDisplayConfiguration()
{
    WriteToDisplay(
        OLEDStrings::ConfigSavingLine1,
        OLEDStrings::ConfigSavingLine2,
        OLEDStrings::ConfigSavingLine3
    );

    // true on success
    bool result = configManager.WriteDisplayConfigurationMode(selectedConfiguration);

    delay(CONFIG_DISPLAY_DELAY);

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

    delay(CONFIG_DISPLAY_DELAY);

    SetState(SelectState::GetInstance());
}

void ConfigStateMachine::Restart()
{
    system->Restart();
}