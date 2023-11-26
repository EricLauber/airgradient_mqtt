#ifndef MockHTSensor_h
#define MockHTSensor_h

#include <IHTSensor.h>

namespace IO
{
    class MockHTSensor : public IHTSensor
    {
        public:
            float GetHumidity() override { return 0.46; };
            float GetTemperature() override { return 37.0; };
    };
}

#endif