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
        IHTSensor* htSensor;
        IGasIndexSensor* gasIndexSensor;
        ICO2Sensor* co2Sensor;
        //ConfigStateMachine* configStateMachine;

    public:
        AirGradientPro(IDisplay* display, IButton* button, ISoC* soc, IHTSensor* htSensor, IGasIndexSensor* gasIndexSensor, ICO2Sensor* co2Sensor);
        void Startup();
        void SetupSensors();
        void Run();

        // Display
        int WriteToDisplay(String line1, String line2, String line3);

        void RunConfigStateMachine();
};


#endif