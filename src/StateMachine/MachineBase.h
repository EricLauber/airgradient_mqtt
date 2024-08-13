#ifndef MachineBase_h
#define MachineBase_h

class StateBase;

// todo - wrap around RTTI switchboard directive
enum class MachineType
{
  BASE = 0,
  CONFIG = 1
};

class MachineBase
{
    public:
        virtual void Run() = 0;
        void SetState(StateBase& newState);
        StateBase *GetState();

        // todo - wrap around RTTI switchboard directive
        // todo - describe dynamic_cast-related issues
        MachineType GetClassType() const;
        void SetClassType(const MachineType classType);

        MachineBase(MachineType classType);

    protected:
        StateBase *state;

    // todo - wrap around RTTI switchboard directive
    private:
        MachineType classType;
};

#endif