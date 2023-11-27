#ifndef SensirionGasIndexSensor_h
#define SensirionGasIndexSensor_h

#include "../IGasIndexSensor.h"
#include <Arduino.h>
#include <SensirionI2CSgp41.h>
#include <NOxGasIndexAlgorithm.h>
#include <VOCGasIndexAlgorithm.h>


namespace IO::GasIndex
{
    class SensirionGasIndexSensor : public IGasIndexSensor
    {
        private:
            SensirionI2CSgp41 sgp41;
            // putting the algorithm objects here weirdly causes build issues.
            //VOCGasIndexAlgorithm voc_algorithm;
            //NOxGasIndexAlgorithm nox_algorithm;

            // time in seconds needed for NOx conditioning
            uint16_t conditioning_s = 10;
            uint16_t srawVoc = 0;
            uint16_t srawNox = 0;

            uint16_t error;
            
            uint16_t compensationRh = 0;              // in ticks as defined by SGP41
            uint16_t compensationT = 0;               // in ticks as defined by SGP41

        public:
            void SetCompenstation(float temperature, float humidity) override;
            float GetTVOCIndex() override;
            float GetNOXIndex() override;
            
            SensirionGasIndexSensor(TwoWire wire);
    };
}
#endif