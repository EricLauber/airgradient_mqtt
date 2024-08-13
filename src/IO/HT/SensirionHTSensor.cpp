#include "SensirionHTSensor.h"

namespace IO::HT
{
    float SensirionHTSensor::GetHumidity()
    {
        return sht.getHumidity();
    }

    float SensirionHTSensor::GetTemperature()
    {
        return sht.getTemperature();
    }

    SensirionHTSensor::SensirionHTSensor()
    {
        this->sht.init();
        this->sht.setAccuracy(SHTSensor::SHT_ACCURACY_MEDIUM);
    }
}