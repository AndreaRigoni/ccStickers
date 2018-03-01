
#include <Core/foreach.h>
#include <Math/Histogram.h>
#include <Graphic2D/Curve2D.h>

////////////////////////////////////////////////////////////////////////////////
//  CURVE 2D  //////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void Curve2D::PrintSelf_abs(std::ostream &o, int nbins) const
{
    Histogram<double> to_hist;
    const std::string name = this->GetName();
    if (XAxis().limits[0] == XAxis().limits[1]) {
        double min=0,max=0;
        foreach(const Point &pt, m_data) {
            if(pt(0)<min) min=pt(0);
            if(pt(0)>max) max=pt(0);
        }
        to_hist = Histogram<double> (name.c_str(),nbins,min,max);
    }
    else
        to_hist = Histogram<double>(name.c_str(),nbins,XAxis().limits[0], XAxis().limits[1]);
    foreach(const Point &pt, m_data) {
        to_hist.Push(pt(0),pt(1));
    }
    o << to_hist;
}
