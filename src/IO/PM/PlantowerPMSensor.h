#ifndef PlantowerPMSensor_h
#define PlantowerPMSensor_h

#include "../IPMSensor.h"
#include "../../Switchboard.h"
#include "ParticulateMatterSample.h"
#include <Arduino.h>
#include <Stream.h>
//#include SOFTWARE_SERIAL_LIBRARY

namespace IO::PM
{
    class PlantowerPMSensor : public IPMSensor
    {
        private:
            
            enum STATUS { STATUS_WAITING, STATUS_OK };
            enum MODE { MODE_ACTIVE, MODE_PASSIVE };

            uint8_t _payload[32];
            Stream* _stream;
            ParticulateMatterSample* _data;
            STATUS _PMSstatus;
            MODE _mode = MODE_ACTIVE;

            uint8_t _index = 0;
            uint16_t _frameLen;
            uint16_t _checksum;
            uint16_t _calculatedChecksum;

        public:

            void requestRead();
            bool readUntil(ParticulateMatterSample& data, uint16_t timeout = 1);
            void loop();


            int GetPM1_0Raw() override;
            int GetPM2_5Raw() override;
            int GetPM10_0Raw() override;

            int GetPM0_5Count() override;
            int GetPM0_3Count() override;
            int GetPM1_0Count() override;
            int GetPM2_5Count() override;
            int GetPM5_0Count() override;
            int GetPM10_0Count() override;
            
            PlantowerPMSensor();

            // struct DATA
            // {
            //     // Standard Particles, CF=1
            //     uint16_t PM_SP_UG_1_0;
            //     uint16_t PM_SP_UG_2_5;
            //     uint16_t PM_SP_UG_10_0;

            //     // Atmospheric environment
            //     uint16_t PM_AE_UG_1_0;
            //     uint16_t PM_AE_UG_2_5;
            //     uint16_t PM_AE_UG_10_0;

            //     // Raw particles count (number of particles in 0.1l of air
            //     uint16_t PM_RAW_0_3;
            //     uint16_t PM_RAW_0_5;
            //     uint16_t PM_RAW_1_0;
            //     uint16_t PM_RAW_2_5;
            //     uint16_t PM_RAW_5_0;
            //     uint16_t PM_RAW_10_0;

            //     // Formaldehyde (HCHO) concentration in mg/m^3 - PMSxxxxST units only
            //     uint16_t AMB_HCHO;

            //     // Temperature & humidity - PMSxxxxST units only
            //     int16_t PM_TMP;
            //     uint16_t PM_HUM;
            // };
    };
}
#endif