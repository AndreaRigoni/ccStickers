#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

#include <iostream>
#include "Core/Named.h"
#include "Math/StatisticGen.h"
#include "Math/StatisticUtils.h"


////////////////////////////////////////////////////////////////////////////////
//  Accumulator  ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template < typename T >
class Accumulator : public Named
{
public:
    Accumulator() : Named() {}

    Accumulator(const Accumulator &other) :
        Named(other),
        m_min(other.m_min), m_max(other.m_max), m_sum(other.m_sum),
        m_stat(other.m_stat)
    {}

    Accumulator(const char *name) :
        Named(name),
        m_min(0),
        m_max(0),
        m_sum(0)
    {}


    void Push(const T data) {
        if(this->Size()) {
            m_min = std::min(m_min,data);
            m_max = std::max(m_max,data);
        } else {
            m_min = m_max = data;
        }
        m_sum += data;
        m_stat << data;
    }

    inline void operator << (const T data) { Push(data); }

    void Clear() {
        m_min = m_max = m_sum = 0;
        m_stat.clear();
    }

    T Max() const { return m_max; }
    T Min() const { return m_min; }
    T Sum() const { return m_sum; }

    size_t Size() const { return m_stat.size(); }
    double Mean() const { return m_stat.mean(); }
    double Variance() const { return m_stat.variance(); }
    double Rms() const { return m_stat.rms(); }

    void operator += (const Accumulator &other) {
        if(this->Size()) {
            m_min = std::min(m_min, other.m_min);
            m_max = std::max(m_max, other.m_max);
        } else {
            m_min = other.m_min;
            m_max = other.m_max;
        }
        m_sum  += other.m_sum;
        m_stat += other.m_stat; // see stat operator //
    }

    void PrintSelfInline(std::ostream &o) const {
        o << "Accumulator(\"" << this->GetName() << "\") [" << m_min << "," << m_max << "]"
          << " tot:" << m_sum << " mean:" << Mean() << " rms:" << Rms();
    }

    /// Print to ostreem
    friend std::ostream &
    operator << (std::ostream &o, const Accumulator<T> &_this) {
        _this.PrintSelfInline(o);
        return o;
    }

    template < class Archive >
    friend void serialize(Archive &ar, Accumulator &h) {
        ar & h.m_min & h.m_max & h.m_sum & h.m_stat;
        ar & (Named &)h;
    }

protected:
    T m_min,m_max,m_sum;
    StatUtils::IncrementalOrder2 m_stat;
};

#endif // ACCUMULATOR_H

