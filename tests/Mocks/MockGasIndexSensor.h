#ifndef MockGasIndexSensor_h
#define MockGasIndexSensor_h

#include <IGasIndexSensor.h>

namespace IO
{
    class MockGasIndexSensor : public IGasIndexSensor
    {
        public:
            float Temperature;
            float Humidity;
            void SetCompenstation(float temperature, float humidity) override
            {
                Temperature = temperature;
                Humidity = humidity;
            };
            float GetTVOCIndex() override { return 4.0; };
            float GetNOXIndex() override { return 3.0; };
    };
}

#endif