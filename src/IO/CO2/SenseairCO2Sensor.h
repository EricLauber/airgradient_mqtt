#ifndef SenseairCO2Sensor_h
#define SenseairCO2Sensor_h

#include "../ICO2Sensor.h"
#include "../../Switchboard.h"
#include <Arduino.h>
#include SOFTWARE_SERIAL_LIBRARY

namespace IO::CO2
{
    class SenseairCO2Sensor : public ICO2Sensor
    {
        private:
            SOFTWARE_SERIAL *softwareSerialCO2;

        public:
            int GetAverageCO2(int numberOfSamplesToTake) override;
            int GetCO2Raw() override;
            
            SenseairCO2Sensor();
    };
}
#endif