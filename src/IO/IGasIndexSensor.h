#ifndef IGasIndexSensor_h
#define IGasIndexSensor_h

namespace IO
{
    // This interface provides input from a gas index sensor.
    class IGasIndexSensor
    {
        public:
            virtual void SetCompenstation(float temperature, float humidity) = 0;
            virtual float GetTVOCIndex() = 0;
            virtual float GetNOXIndex() = 0;
    };
}

#endif