#ifndef AirGradientPro_h
#define AirGradientPro_h

#include "../Switchboard.h"
#include <Arduino.h>
#include "../Display/Display.h"
#include "../IO/IO.h"
#include "../StateMachine/StateMachine.h"

using namespace Display;
using namespace IO;
using namespace Data;

class AirGradientPro
{
    private:
        IDisplay* display;
        IButton* button;
        ISoC* soc;
        //ConfigStateMachine* configStateMachine;

    public:
        AirGradientPro(IDisplay* display, IButton* button, ISoC* soc);
        void Startup();
        void SetupSensors();
        void Run();

        // Display
        int WriteToDisplay(String line1, String line2, String line3);

        void RunConfigStateMachine();
};


#endif