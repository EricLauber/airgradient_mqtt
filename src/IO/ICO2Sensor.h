#ifndef ICO2Sensor_h
#define ICO2Sensor_h

namespace IO
{
    // This interface provides input from a carbon dioxide sensor.
    class ICO2Sensor
    {
        public:
            virtual int GetAverageCO2(int numberOfSamplesToTake) = 0;
            virtual int GetCO2Raw() = 0;
    };
}

#endif