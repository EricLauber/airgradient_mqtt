#ifndef PlantowerPMSensor_h
#define PlantowerPMSensor_h

#include "../IPMSensor.h"
#include "../../Switchboard.h"
#include <Arduino.h>
//#include SOFTWARE_SERIAL_LIBRARY

namespace IO::PM
{
    class PlantowerPMSensor : public IPMSensor
    {
        // private:
        //     SOFTWARE_SERIAL *softwareSerialCO2;

        public:
            int GetPM1_0Raw() override;
            int GetPM2_5Raw() override;
            int GetPM10_0Raw() override;

            int GetPM0_5Count() override;
            int GetPM0_3Count() override;
            int GetPM1_0Count() override;
            int GetPM2_5Count() override;
            int GetPM5_0Count() override;
            int GetPM10_0Count() override;
            
            PlantowerPMSensor();
    };
}
#endif