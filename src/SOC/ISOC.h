#ifndef ISOC_h
#define ISOC_h

namespace SOC
{
    // This interface provides output to the system.
    class ISOC
    {
        public:
            virtual void Reset() = 0;
            virtual void Restart() = 0;
            virtual int GetChipID() = 0;
    };
}

#endif