#ifndef SensirionGasIndexSensor_h
#define SensirionGasIndexSensor_h

#include "../IGasIndexSensor.h"
// is this include required?
#include <Wire.h>
#include <Arduino.h>
#include <SensirionI2CSgp41.h>
#include <NOxGasIndexAlgorithm.h>
#include <VOCGasIndexAlgorithm.h>


namespace IO::Input
{
    class SensirionGasIndexSensor : public IGasIndexSensor
    {
        private:
            SensirionI2CSgp41 sgp41;
            VOCGasIndexAlgorithm voc_algorithm;
            //NOxGasIndexAlgorithm nox_algorithm;

            // time in seconds needed for NOx conditioning
            uint16_t conditioning_s = 10;
            char errorMessage[256];
            uint16_t srawVoc = 0;
            uint16_t srawNox = 0;

            uint16_t error;
            
            //uint16_t defaultRh = 0x8000;
            //uint16_t defaultT = 0x6666;
            
            //uint16_t defaultCompenstaionRh = 0x8000;  // in ticks as defined by SGP41
            //uint16_t defaultCompenstaionT = 0x6666;   // in ticks as defined by SGP41
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