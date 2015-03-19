#ifndef PLOT2D_H
#define PLOT2D_H

#include <vector>
#include "Core/Flags.h"
#include "Core/Named.h"
#include "Core/Singleton.h"

#include "Graphic2D/Curve2D.h"
#include "Graphic2D/ColorRGBList.h"

////////////////////////////////////////////////////////////////////////////////
//  Plot  //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class Plot2D : public Named
{
public:

    typedef Curve2D        CurveType;
    typedef Curve2D::Axis  AxisType;
    typedef Curve2D::Point PointType;

    Plot2D(const char *name) : Named(name) {}

    size_t GetNumberOfPlots() const { return m_curves.size(); }

    void AddCurve(const Curve2D &curve) {
         m_curves.push_back(curve);
         m_curves_flags.push_back( OptionFlags(ShowLines | ShowPoints | Smoothed) );
         if(m_Xaxis.empty()) m_Xaxis.push_back(curve.XAxis());
         if(m_Yaxis.empty()) m_Yaxis.push_back(curve.YAxis());
    }

    inline AxisType & XAxis(unsigned int i = 0) { return m_Xaxis.at(i); }
    inline const AxisType & XAxis(unsigned int i = 0) const { return m_Xaxis.at(i); }
    inline AxisType & YAxis(unsigned int i = 0) { return m_Yaxis.at(i); }
    inline const AxisType & YAxis(unsigned int i = 0) const { return m_Yaxis.at(i); }

    std::string GetSubtitle() const { return m_subtitle; }
    void SetSubtitle(const std::string &subtitle) { m_subtitle = subtitle; }

    Curve2D & Curve(int i) { return m_curves[i]; }

    void PrintToCsv( std::ostream &o, const char sep = ';' );

    void PrintToCsv( std::string file_name, const char sep = ';' );

    void PrintToGnuplotFile(std::string file_name = "") const;

//    friend CsvDataFile &
//    operator << (CsvDataFile &csv, Plot2D &plot) {
//        plot.PrintToCsv(csv, csv.Separator());
//        return csv;
//    }

    enum OptionEnum {
        Smoothed    = 1 << 0,
        ShowLines   = 1 << 1,
        ShowPoints  = 1 << 2,
        ShowBars    = 1 << 3
    };
    typedef Flags<enum OptionEnum> OptionFlags;

    OptionFlags & CurveFlags(unsigned int i) { return m_curves_flags[i]; }
    const OptionFlags & CurveFlags(unsigned int i) const { return m_curves_flags[i]; }

private:
    std::vector<AxisType> m_Xaxis;
    std::vector<AxisType> m_Yaxis;
    std::vector<Curve2D>     m_curves;
    std::vector<OptionFlags> m_curves_flags;

    std::string m_subtitle;

    static Singleton<ColorRGBList> s_chart_colors;

};


DEFINE_OPERATORS_FOR_FLAGS(Plot2D::OptionFlags)


#endif // PLOT2D_H

