#ifndef SensirionHTSensor_h
#define SensirionHTSensor_h

#include "../IHTSensor.h"
// this might not work
#include <SHTSensor.h>


namespace IO::Input
{
    class SensirionHTSensor : public IHTSensor
    {
        private:
            SHTSensor sht;

        public:
            virtual float GetHumidity() override;
            virtual float GetTemperature() override;
            
            SensirionHTSensor();
    };
}
#endif