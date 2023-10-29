#include "AirGradientPro.h"

using namespace Display;
using namespace Input;
using namespace Output;
using namespace Data;

AirGradientPro::AirGradientPro(IDisplay* display, IButton* button, ISystem* system)
{
    this->display = display;
    this->button = button;
    this->system = system;
    
}