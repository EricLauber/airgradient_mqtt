#ifndef ISoC_h
#define ISoC_h

namespace IO
{
    // This interface provides output to the system.
    class ISoC
    {
        public:
            virtual void Reset() = 0;
            virtual void Restart() = 0;
            virtual int GetChipID() = 0;
    };
}

#endif