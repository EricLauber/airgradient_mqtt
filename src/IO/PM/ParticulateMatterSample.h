#ifndef ParticulateMatterSample_h
#define ParticulateMatterSample_h

namespace IO::PM
{
    class ParticulateMatterSample
    {
        public:
            // Standard Particles, CF=1
            uint16_t PM_SP_UG_1_0;
            uint16_t PM_SP_UG_2_5;
            uint16_t PM_SP_UG_10_0;

            // Atmospheric environment
            uint16_t PM_AE_UG_1_0;
            uint16_t PM_AE_UG_2_5;
            uint16_t PM_AE_UG_10_0;

            // Raw particles count (number of particles in 0.1l of air
            uint16_t PM_RAW_0_3;
            uint16_t PM_RAW_0_5;
            uint16_t PM_RAW_1_0;
            uint16_t PM_RAW_2_5;
            uint16_t PM_RAW_5_0;
            uint16_t PM_RAW_10_0;

            // Formaldehyde (HCHO) concentration in mg/m^3 - PMSxxxxST units only
            uint16_t AMB_HCHO;

            // Temperature & humidity - PMSxxxxST units only
            int16_t PM_TMP;
            uint16_t PM_HUM;
    };
}

#endif