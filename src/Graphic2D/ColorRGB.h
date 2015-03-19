#ifndef COLORRGB
#define COLORRGB

#include <string>

#include "Math/ScalarArray.h"

////////////////////////////////////////////////////////////////////////////////
//  ColorRGB  //////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class ColorRGB : public ScalarArray<unsigned char,3>
{
    typedef ScalarArray<unsigned char,3> BaseClass;
    typedef BaseClass::ScalarType ScalarType;

public:
    ColorRGB() {}

    ColorRGB(const ScalarType R,const ScalarType G,const ScalarType B) : BaseClass(R,G,B) {}
    ColorRGB(const char *SharpRGB);

    ScalarType & R() { return this->operator ()(0); }
    const ScalarType & R() const { return this->operator ()(0); }
    ScalarType & G() { return this->operator ()(1); }
    const ScalarType & G() const { return this->operator ()(1); }
    ScalarType & B() { return this->operator ()(2); }
    const ScalarType & B() const { return this->operator ()(2); }

    std::string ToString() const;

private:

};


#endif // COLORRGB

