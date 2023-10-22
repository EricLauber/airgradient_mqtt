#ifndef ISystem_h
#define ISystem_h

namespace Output
{
    // This interface provides output to the system.
    class ISystem
    {
        public:
            virtual void Reset() = 0;
            virtual void Restart() = 0;
    };
}

#endif