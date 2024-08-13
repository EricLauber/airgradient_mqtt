#ifndef MockDisplay_h
#define MockDisplay_h

#include <WString.h>
#include <IDisplay.h>

namespace Display
{
    class MockDisplay : public IDisplay
    {
        public:
            String Line1 = "";
            String Line2 = "";
            String Line3 = "";
            
            // Update text on the display. Returns 0 once drawing is complete.
            int WriteLines(String line1, String line2, String line3) override
            {
                this->Line1 = line1;
                this->Line2 = line2;
                this->Line3 = line3;
                return 0;
            }
    };
}

#endif