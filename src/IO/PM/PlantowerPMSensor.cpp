#include "PlantowerPMSensor.h"

namespace IO::PM
{
    PlantowerPMSensor::PlantowerPMSensor()
    {
        if (DEBUG_ENABLED) 
        {
            Serial.println("Initializing CO2...");
        }
        
        
    }


    int PlantowerPMSensor::GetPM1_0Raw() { return 0; };
    int PlantowerPMSensor::GetPM2_5Raw() { return 0; };
    int PlantowerPMSensor::GetPM10_0Raw() { return 0; };

    int PlantowerPMSensor::GetPM0_5Count() { return 0; };
    int PlantowerPMSensor::GetPM0_3Count() { return 0; };
    int PlantowerPMSensor::GetPM1_0Count() { return 0; };
    int PlantowerPMSensor::GetPM2_5Count() { return 0; };
    int PlantowerPMSensor::GetPM5_0Count() { return 0; };
    int PlantowerPMSensor::GetPM10_0Count() { return 0; };
}