#ifndef SensirionHTSensor_h
#define SensirionHTSensor_h

#include "../IHTSensor.h"
#include <SHTSensor.h>

namespace IO::HT
{
    class SensirionHTSensor : public IHTSensor
    {
        private:
            SHTSensor sht;

        public:
            float GetHumidity() override;
            float GetTemperature() override;
            
            SensirionHTSensor();
    };
}
#endif