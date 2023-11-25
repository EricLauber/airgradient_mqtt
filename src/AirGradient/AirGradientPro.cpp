#include "AirGradientPro.h"

using namespace Display;
using namespace IO;
using namespace Data;

AirGradientPro::AirGradientPro(IDisplay* display, IButton* button, ISoC* soc)
{
    this->display = display;
    this->button = button;
    this->soc = soc;
    
}

void AirGradientPro::Startup()
{
    // Step 1. Alert the user to startup
    Serial.begin(115200);

    WriteToDisplay(
        OLEDStrings::StartupConfigPromptLine1,
        OLEDStrings::StartupConfigPromptLine2,
        OLEDStrings::StartupConfigPromptLine3
    );

    // Step 2. Check if the user is entering config mode
    button->UpdateButtonInput(BUTTON_TIMEOUT);

    button->UpdateButtonInput(4000);
    //if (!button->LongPressed && !button->SingleClicked)
    if (button->LongPressed || button->SingleClicked)
    {
#if DEBUG_ENABLED == 1
    Serial.println("Button press detected. Entering configuration mode.");
#endif
        RunConfigStateMachine();
    }
    else
    {
#if DEBUG_ENABLED == 1
    Serial.println("No button detected. Begin sensor setup.");
#endif
        SetupSensors();
    }
}

void AirGradientPro::SetupSensors()
{
    /*

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

int AirGradientPro::WriteToDisplay(String line1, String line2, String line3)
{
    return display->WriteLines(line1, line2, line3);
}

void AirGradientPro::RunConfigStateMachine()
{
    //configStateMachine = new ConfigStateMachine(display, button, soc);
    ConfigStateMachine configStateMachine = ConfigStateMachine(display, button, soc);
    // Loop forever, until the user selects the Reboot option.
    for (;;)
    {
        //configStateMachine->Run();
        configStateMachine.Run();
        delay(100);
    }
}