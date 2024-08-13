#ifndef IPMSensor_h
#define IPMSensor_h

namespace IO
{
    // This interface provides input from a particulate matter sensor.
    class IPMSensor
    {
        public:
            virtual int GetPM1_0Raw() = 0;
            virtual int GetPM2_5Raw() = 0;
            virtual int GetPM10_0Raw() = 0;

            virtual int GetPM0_5Count() = 0;
            virtual int GetPM0_3Count() = 0;
            virtual int GetPM1_0Count() = 0;
            virtual int GetPM2_5Count() = 0;
            virtual int GetPM5_0Count() = 0;
            virtual int GetPM10_0Count() = 0;
    };
}

#endif