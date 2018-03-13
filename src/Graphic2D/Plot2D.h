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



    static const size_t SET_SIZE = 2;

    Plot2D(const char *name)
        : Named(name)
    {}

    size_t GetNumberOfPlots(int set = 0) const { return d[set].m_curves.size(); }

    void AddCurve(const Curve2D &curve, int set = 0) {
        // do not change axes if they were touched //
        if(d[set].m_curves.empty() && d[set].m_Xaxis.empty() && d[set].m_Yaxis.empty()) {
            d[set].m_Xaxis = curve.XAxis(); // first curve Axis is plot axis //
            d[set].m_Yaxis = curve.YAxis(); // first curve Axis is plot axis //
        }
        d[set].m_curves.push_back(curve);
        d[set].m_curves_flags.push_back( OptionFlags(ShowLines | ShowPoints | Smoothed) );
    }

    inline AxisType & XAxis(size_t set = 0) { return d[set].m_Xaxis; }
    inline const AxisType & XAxis(size_t set = 0) const { return d[set].m_Xaxis; }
    inline AxisType & YAxis(size_t set = 0) { return d[set].m_Yaxis; }
    inline const AxisType & YAxis(size_t set = 0) const { return d[set].m_Yaxis; }

    std::string GetSubtitle() const { return m_subtitle; }
    void SetSubtitle(const std::string &subtitle) { m_subtitle = subtitle; }

    Curve2D & Curve(size_t i, size_t set = 0) { return d[set].m_curves[i]; }
    const Curve2D & Curve(size_t i, size_t set = 0) const { return d[set].m_curves[i]; }

    std::vector<Curve2D> & Curves(size_t set = 0) { return d[set].m_curves; }
    const std::vector<Curve2D> & Curves(size_t set = 0) const { return d[set].m_curves; }

    void PrintToCsv( std::string file_name, const char sep = ';' );


    enum GnuplotStyle {
        GnuplotStyle1,
        GnuplotStyle2,
    };
    void PrintToGnuplotFile(std::string file_name = "", enum GnuplotStyle = GnuplotStyle2) const;

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

    OptionFlags & CurveFlags(size_t i, size_t set = 0) { return d[set].m_curves_flags[i]; }
    const OptionFlags & CurveFlags(size_t i, size_t set = 0) const { return d[set].m_curves_flags[i]; }

private:
    typedef struct {
        AxisType                 m_Xaxis;
        AxisType                 m_Yaxis;
        std::vector<Curve2D>     m_curves;
        std::vector<OptionFlags> m_curves_flags;
    } PlotSet;

    PlotSet d[SET_SIZE];
    std::string m_subtitle;
    static Singleton<ColorRGBList> s_chart_colors;

    void print_plot_range(std::ofstream &o) const;
    void print_plot_scale(std::ofstream &o) const;
    void print_plot_style1(const std::string &name, std::ofstream &o) const;
    void print_plot_style2(const std::string &name, std::ofstream &o) const;
};

DEFINE_OPERATORS_FOR_FLAGS(Plot2D::OptionFlags)





#endif // PLOT2D_H

