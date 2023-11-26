#include "SensirionGasIndexSensor.h"

namespace IO::Input
{
    SensirionGasIndexSensor::SensirionGasIndexSensor(TwoWire wire)
    {
        sgp41.begin(wire);
    }

    // maybe this should return the error value?
    void SensirionGasIndexSensor::SetCompenstation(float temperature, float humidity)
    {
        compensationT = static_cast<uint16_t>((temperature + 45) * 65535 / 175);
        compensationRh = static_cast<uint16_t>(humidity * 65535 / 100);

        if (conditioning_s > 0)
        {
            error = sgp41.executeConditioning(compensationRh, compensationT, srawVoc);
            conditioning_s--;
        }
        else
        {
            error = sgp41.measureRawSignals(compensationRh, compensationT, srawVoc, srawNox);
        }
    }

    float SensirionGasIndexSensor::GetTVOCIndex()
    {
        VOCGasIndexAlgorithm voc_algorithm;
        return voc_algorithm.process(srawVoc);
    }

    float SensirionGasIndexSensor::GetNOXIndex()
    {
        NOxGasIndexAlgorithm nox_algorithm;
        return nox_algorithm.process(srawNox);
    }
}