#ifndef AirGradientPro_h
#define AirGradientPro_h

#include "../Switchboard.h"
#include <Arduino.h>
#include "../Display/Display.h"
#include "../Input/Input.h"
#include "../SOC/SOC.h"
#include "../StateMachine/StateMachine.h"

using namespace Display;
using namespace Input;
using namespace SOC;
using namespace Data;

class AirGradientPro
{
    private:
        IDisplay* display;
        IButton* button;
        ISOC* soc;
        //ConfigStateMachine* configStateMachine;

    public:
        AirGradientPro(IDisplay* display, IButton* button, ISOC* soc);
        void Startup();
        void Run();

        // Display
        int WriteToDisplay(String line1, String line2, String line3);

        void RunConfigStateMachine();
};


#endif