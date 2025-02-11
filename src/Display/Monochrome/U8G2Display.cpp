#include <U8g2lib.h>
#include <WString.h>
#include "U8G2Display.h"

namespace Display::Monochrome
{
    // Update text on the display. Returns 0 once drawing is complete.
    int U8G2Display::WriteLines(String line1, String line2, String line3)
    {
        int result = 0;

        //char buf[9];
        u8g2.firstPage();
        do 
        {
            u8g2.setFont(u8g2_font_t0_16_tf);
            u8g2.drawStr(1, 10, String(line1).c_str());
            u8g2.drawStr(1, 30, String(line2).c_str());
            u8g2.drawStr(1, 50, String(line3).c_str());
        } 
        while ( result |= u8g2.nextPage() );
        
        return result;
    }

    U8G2Display::U8G2Display(U8G2 display)
    {
        this->u8g2 = display;
        u8g2.begin();
        u8g2.setDisplayRotation(U8G2_R0);
    }
}