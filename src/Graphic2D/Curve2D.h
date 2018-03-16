#ifndef CURVE2D_H
#define CURVE2D_H

#include <iostream>
#include <algorithm>
#include <vector>

#include "Math/ScalarArray.h"
#include "Core/Named.h"


////////////////////////////////////////////////////////////////////////////////
//  Curve2D  ////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class Curve2D : /*Lockable,*/ public Named
{
public:
    typedef Vector3d Point;   // (X, Y, RMS ERROR) //

public:


    struct Axis {
        std::string name;
        double limits[2];
        double ticks;
        enum ScaleEnum {
            LinScale,
            LogScale
        } scale_type;

        Axis() :
            ticks(1),
            scale_type(LinScale)
        {
            limits[0] = 0;
            limits[1] = 0;
        }

        bool empty() const {
            return name == ""
                    && limits[0] == 0
                    && limits[1] == 0
                    && ticks == 1;
        }

        bool operator == (const Axis &other) const {
            return this->name == other.name
                    && this->limits[0] == other.limits[0]
                    && this->limits[1] == other.limits[1]
                    && this->ticks == other.ticks;
        }

        void SetScaleType(const enum ScaleEnum scale) {
            this->scale_type = scale;
        }
    };

    Curve2D() {}

    Curve2D(const char *name) :
        Named(name)
    {}

    size_t Size() const { return m_data.size(); }

    template < typename _T >
    void AddPoint( const ScalarArray<_T,3> &pt ) {
        //  MDS_LOCK_SCOPE(*this);
        m_data.push_back ( (Point)pt );
    }

    friend std::ostream &
    operator << (std::ostream &o, const Curve2D &curve) {
        o<< "Curve: " << curve.GetName() << "\n";
        for(size_t i=0; i<curve.m_data.size(); ++i) {
            const Point &pt = curve.m_data[i];
            o << pt(0) << "," << pt(1) << "\n";
        }
        return o;
    }

    void Update() {
        //        for(size_t i = 0; i < m_data.size(); ++i) {
        //            XAxis().limits[0] = std::min( min, m_data.at(i)(0) );
        //            XAxis().limits[1] = std::max( max, m_data.at(i)(0) );
        //            YAxis().limits[0] = std::min( min, m_data.at(i)(1) );
        //            YAxis().limits[1] = std::max( max, m_data.at(i)(1) );
        //        }
        std::sort(m_data.begin(),m_data.end());
    }

    inline Axis & GetAxis(unsigned int i) { return m_axis[i]; }
    inline const Axis & GetAxis(unsigned int i) const { return m_axis[i]; }
    inline Axis & XAxis() { return GetAxis(0); }
    inline const Axis & XAxis() const { return GetAxis(0); }
    inline Axis & YAxis() { return GetAxis(1); }
    inline const Axis & YAxis() const { return GetAxis(1); }

    std::vector<Point> &Points() { return m_data; }
    const std::vector<Point> &Points() const { return m_data; }

    Point & operator[](size_t id) { return m_data[id]; }
    const Point & operator[](size_t id) const { return m_data[id]; }

    void PrintSelf_abs(std::ostream &o, int nbins) const;

private:
    std::vector<Point> m_data;
    Axis m_axis[2];
};


#endif // CURVE2D_H

