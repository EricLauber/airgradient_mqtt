#ifndef MockCO2Sensor_h
#define MockCO2Sensor_h

#include <ICO2Sensor.h>

namespace IO
{
    class MockCO2Sensor : public ICO2Sensor
    {
        public:
            int GetAverageCO2(int numberOfSamplesToTake) override { return 600; };
            int GetCO2Raw() override { return 600; };
    };
}

#endif