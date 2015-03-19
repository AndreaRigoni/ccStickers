#ifndef COLORRGBLIST
#define COLORRGBLIST

#include <vector>
#include "Graphic2D/ColorRGB.h"


////////////////////////////////////////////////////////////////////////////////
//  ColorRGBList  //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class ColorRGBList
{
public:
    ColorRGBList() {}

    struct Entry {
        std::string name;
        ColorRGB    color;
        Entry(const std::string n, const ColorRGB c) : name(n), color(c) {}
    };

    const std::vector<Entry> & ColorList() const { return m_color_list; }
    std::vector<Entry> & ColorList() { return m_color_list; }

    std::vector<Entry> & operator ()() {
        return ColorList();
    }

private:
    std::vector<Entry> m_color_list;
};




#endif // COLORRGBLIST

