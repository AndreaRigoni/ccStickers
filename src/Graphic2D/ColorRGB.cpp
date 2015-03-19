#include "ColorRGB.h"

#include "stdio.h"

////////////////////////////////////////////////////////////////////////////////
//  ColorRGB  //////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <sstream>


ColorRGB::ColorRGB(const char *SharpRGB)
{
    std::stringstream ss(SharpRGB);
    char c;
    unsigned int num;
    ss >> c >> std::hex >> num;

    R() = (num / 0x10000) % 0x10000;
    G() = (num / 0x100) % 0x100;
    B() = num % 0x100;
}

std::string ColorRGB::ToString() const
{
    char str[8];
    sprintf(str,"#%02x%02x%02x", R(),G(),B());
    return std::string(str);
}


