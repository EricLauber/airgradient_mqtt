#ifndef AirGradientPro_h
#define AirGradientPro_h

#include "../Switchboard.h"
#include "../Display/Display.h"
#include "../Input/Input.h"
#include "../Output/Output.h"
#include "../StateMachine/StateMachine.h"

using namespace Display;
using namespace Input;
using namespace Output;
using namespace Data;

class AirGradientPro
{
    private:
        IDisplay* display;
        IButton* button;
        ISystem* system;

    public:
        AirGradientPro(IDisplay* display, IButton* button, ISystem* system);
        void Startup();
        void Run();
};


#endif