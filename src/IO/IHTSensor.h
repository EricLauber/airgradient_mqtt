#ifndef IHTSensor_h
#define IHTSensor_h

namespace IO
{
    // This interface provides input from a humidity temperature sensor.
    class IHTSensor
    {
        public:
            virtual float GetHumidity() = 0;
            virtual float GetTemperature() = 0;
    };
}

#endif