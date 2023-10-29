#include "AirGradientPro.h"

using namespace Display;
using namespace Input;
using namespace Output;
using namespace Data;

AirGradientPro::AirGradientPro(IDisplay* display, IButton* button, ISystem* system)
{
    this->display = display;
    this->button = button;
    this->system = system;
    
}

void AirGradientPro::Startup()
{
    /*
        1. Detect button push
            if true, start ConfigStateMachine
            1. while loop (forever?)
                {
                    machine.Run
                }

        2.  Init sensors and output
                u8g2 (display)
                Warming up message.
                
                sht
                WIFI
                spg41
                CO2
                PMS
                TMP-RH

    
    */
}

void AirGradientPro::Run()
{
    /*
        Refresh Sensor status

        Update display

        Establish WiFi Connectivity
        Send data to array of servers
    */
}