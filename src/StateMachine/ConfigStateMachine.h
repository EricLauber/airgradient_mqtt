#ifndef ConfigStateMachine_h
#define ConfigStateMachine_h

#include "MachineBase.h"
#include "StateBase.h"
#include "../Display/Display.h"
#include "../Input/Input.h"
#include "../Data/Data.h"
#include "../StringResources.h"

using namespace Display;
using namespace Input;
using namespace Data;

class ConfigStateMachine : public MachineBase
{
    public:
        ConfigStateMachine(IDisplay* display, IButton* button);
        void Run() override;
        int WriteToDisplay(String line1, String line2, String line3);
        void SetDisplayConfiguration(DisplayConfiguration displayConfiguration);
        DisplayConfiguration GetDisplayConfiguration();
        void SaveDisplayConfiguration();

    private:
        IDisplay* display;
        IButton* button;
        ConfigManager configManager;
        DisplayConfiguration selectedConfiguration;
};

class SelectState : public StateBase
{
    public:
    // can this be a configstatemachine or does it have to be statemachine
        //void Enter(ConfigStateMachine* machine);
        void Enter(MachineBase* machine) override;
        void ShortPress(MachineBase* machine) override;
        void LongPress(MachineBase* machine) override;
        void Exit(MachineBase* machine) override;
        static StateBase& GetInstance();
};

class EditConfigState : public StateBase
{
    public:
        void Enter(MachineBase* machine) override;
        void ShortPress(MachineBase* machine) override;
        void LongPress(MachineBase* machine) override;
        void Exit(MachineBase* machine) override;
        static StateBase& GetInstance();
};

class ClearState : public StateBase
{
    public:
        void Enter(MachineBase* machine) override;
        void ShortPress(MachineBase* machine) override;
        void LongPress(MachineBase* machine) override;
        void Exit(MachineBase* machine) override;
        static StateBase& GetInstance();
};

class RebootState : public StateBase
{
    public:
        void Enter(MachineBase* machine) override;
        void ShortPress(MachineBase* machine) override;
        void LongPress(MachineBase* machine) override;
        void Exit(MachineBase* machine) override;
        static StateBase& GetInstance();
};

#pragma region DisplayConfigurationStates

class DisplayConfigTempCμgm3 : public StateBase
{
    public:
        void Enter(MachineBase* machine) override;
        void ShortPress(MachineBase* machine) override;
        void LongPress(MachineBase* machine) override;
        void Exit(MachineBase* machine) override;
        static StateBase& GetInstance();
};

class DisplayConfigTempFμgm3 : public StateBase
{
    public:
        void Enter(MachineBase* machine) override;
        void ShortPress(MachineBase* machine) override;
        void LongPress(MachineBase* machine) override;
        void Exit(MachineBase* machine) override;
        static StateBase& GetInstance();
};

class DisplayConfigTempCAQI : public StateBase
{
    public:
        void Enter(MachineBase* machine) override;
        void ShortPress(MachineBase* machine) override;
        void LongPress(MachineBase* machine) override;
        void Exit(MachineBase* machine) override;
        static StateBase& GetInstance();
};

class DisplayConfigTempFAQI : public StateBase
{
    public:
        void Enter(MachineBase* machine) override;
        void ShortPress(MachineBase* machine) override;
        void LongPress(MachineBase* machine) override;
        void Exit(MachineBase* machine) override;
        static StateBase& GetInstance();
};

#pragma endregion DisplayConfigurationStates

#endif