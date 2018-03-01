#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <vector>
#include <string.h>

#include "Core/CsvDataFile.h"
#include "Math/StatisticUtils.h"
#include "Math/Accumulator.h"
#include "Graphic2D/Curve2D.h"


////////////////////////////////////////////////////////////////////////////////
//  Histogram  /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


template < typename T >
class Histogram : public Accumulator<T>
{

    typedef Accumulator<T> BaseClass;

public:

    Histogram() {} // required by map container //

    Histogram(const char *name, size_t nbin, const T min, const T max) :
        BaseClass(name),
        m_value_name(name),
        m_bins(nbin),
        m_underf(0), m_overf(0)
    { m_limits[0] = min, m_limits[1] = max; }

    void Push(const T data) {
        int bin = this->get_bin(data);
        if(bin < 0)
            ++m_underf;
        else if (bin >= (int)BinSize())
            ++m_overf;
        else {
            //            ++m_bins.at( bin );
            m_bins.at( bin ) += 1.;
            m_stat << data;
        }
        BaseClass::Push(data);
    }

    void Push(const T x, const T y) {
        int bin = this->get_bin(x);
        if(bin < 0)
            ++m_underf;
        else if (bin >= (int)BinSize())
            ++m_overf;
        else {
            m_bins.at( bin ) += y;
            // WARNING ... not weitgh here //
            m_stat << x;
        }
        // WARNING ... not weitgh here //
        BaseClass::Push(x);
    }


    void Clear() {
        std::fill(m_bins.begin(), m_bins.end(), 0);
        m_overf = m_underf = 0;
        m_stat = StatUtils::IncrementalOrder2();
        BaseClass::Clear();
    }

    inline size_t CollectedSize() const { return m_stat.size(); }

    inline size_t BinSize() const { return m_bins.size(); }

    inline void operator<<(const T data) { Push(data); }

    //    inline std::pair<T,size_t> operator[](unsigned int bin) const { return std::make_pair(get_pos(bin),m_bins.at(bin)); }`
    inline std::pair<T,double> operator[](unsigned int bin) const { return std::make_pair(get_pos(bin),m_bins.at(bin)); }

    //    inline size_t operator()(const T pos) const { return m_bins.at(get_bin(pos)); }
    inline double operator()(const T pos) const { return m_bins.at(get_bin(pos)); }

    double Mean() const { return m_stat.mean(); }

    double MeanAll() const { return BaseClass::Mean(); }

    double Variance() const { return m_stat.variance(); }

    double VarianceAll() const { return BaseClass::Variance(); }

    double Rms() const { return m_stat.rms(); }

    double RmsAll() const { return BaseClass::Rms(); }

    void PrintSelf(std::ostream &o, const char _c = ';') const {
        o << "Histogram" << _c << this->m_value_name << "\n";
        for(size_t i=0; i< this->BinSize(); ++i)
            o << this->get_pos(i) << _c << this->m_bins[i] << "\n";
    }

    void PrintSelfInline(std::ostream &o, const char *lut = "_,.-~'`")
    const {
        double max = *std::max_element(m_bins.begin(), m_bins.end());
        o << "(\"" << this->GetName()
          << "\"," << this->BinSize()
          << "," << m_limits[0] << "," << m_limits[1] << ")";
        o << "\t" << m_underf << " [";
        for(size_t i=0; i<this->BinSize(); ++i) {
            double val = (double)m_bins[i];
            unsigned int lid = max > 0 ? (int)floor(val/max * (strlen(lut)-1)) : 0;
            o << lut[lid];
        }
        o << "] " << m_overf << " ";
        o << " card: " << this->Size()
          << " mean:" << this->MeanAll() << " rms:" << this->RmsAll();
    }

    /// Convert to a Curve object
    operator Curve2D () const {
        Curve2D curve(this->GetName().c_str());
        curve.XAxis().name = "Histogram";
        curve.YAxis().name = this->m_value_name;
        for(size_t i=0; i<this->BinSize(); ++i)
            curve.AddPoint( Vector3d(get_pos(i) + get_spacing()/2, m_bins[i]) );
        curve.Update();
        return curve;
    }

    /// external inserter
    template < typename _OtherScalar >
    friend Histogram & operator << (Histogram &h, const _OtherScalar data) {
        h.Push(data);
        return h;
    }


    /// Print to ostreem
    friend std::ostream &
    operator << (std::ostream &o, const Histogram<T> &_this) {
        //        _this.PrintSelf(o);
        _this.PrintSelfInline(o);
        return o;
    }

    /// Print to CSV file
    friend CsvDataFile &
    operator << (CsvDataFile &o, const Histogram &plot) {
        const char _c = o.Separator();
        plot.PrintSelf(o,_c);
        return o;
    }

    Histogram & operator +=( const Histogram &other ) {
        Histogram result = Histogram::merge(*this,other);
        return (*this) = result;
    }

    static Histogram merge(const Histogram &h1, const Histogram &h2) {
        // TODO: very bad ... works only if h have the same bins //
        assert(h1.BinSize() == h2.BinSize());
        assert(h1.m_limits[0] == h2.m_limits[0]);
        assert(h1.m_limits[1] == h2.m_limits[1]);

        Histogram out = h1;
        for(unsigned int i=0; i<h1.BinSize(); ++i) {
            out.m_bins[i] += h2.m_bins[i];
        }
        out.Accumulator<T>::operator +=((Accumulator<T>)h2);
        out.m_stat += h2.m_stat;
        out.m_underf += h2.m_underf;
        out.m_overf += h2.m_overf;

        return out;
    }

    template < class Archive >
    friend void serialize(Archive &ar, Histogram &h) {
        ar
                & (Accumulator<T> &)h
                & h.m_value_name
                & h.m_bins
                & h.m_limits
                & h.m_underf & h.m_overf
                & h.m_stat;
    }


private:

    T get_spacing() const {
        return (m_limits[1] - m_limits[0]) / this->BinSize();
    }

    int get_bin(const T data) const {
        T bin_size = get_spacing();
        return (int)floor( (data-m_limits[0]) /bin_size);
    }

    T get_pos(const int bin) const {
        T bin_size = get_spacing();
        return m_limits[0] + (bin_size) * bin;
    }

    std::string m_value_name;
    //    std::vector<size_t> m_bins;
    std::vector<double> m_bins;
    T m_limits[2];
    size_t m_underf, m_overf;
    StatUtils::IncrementalOrder2 m_stat;
};




#endif // HISTOGRAM_H

