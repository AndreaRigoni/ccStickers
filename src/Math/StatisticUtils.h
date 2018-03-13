#ifndef STAITSTICUTILS_H
#define STAITSTICUTILS_H

#include <cmath>
#include <vector>
#include "stddef.h"

////////////////////////////////////////////////////////////////////////////////
//  INCREMENTAL STATISTICS  ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace detail {
//template<typename T>
//struct sum_kahan
//{
//    sum_kahan() : m_sum(0), m_cps(0) {}
//    void add(const T &val) {
//        const T y = val - m_cps;
//        const T t = m_sum + y;
//        m_cps = (t - m_sum) - y;
//        m_sum = t;
//    }
//    T operator ()() const { return this->m_sum; }
//    inline friend sum_kahan & operator << (sum_kahan &sum, const T &val) {
//        sum.add(val);
//        return sum;
//    }
//private:
//    T m_sum;
//    T m_cps;
//};


template <typename T>
class incremental_order2 {
    size_t m_count;
    T m_mean;
    T m_M2;
public:
    incremental_order2() :
        m_count(0),
        m_mean(0),
        m_M2(0) {}

    void add(const T &data) {
        ++m_count;
        T delta = data - m_mean;
        m_mean += delta/m_count;
        m_M2 += delta*(data - m_mean);
    }

    ///
    /// \brief remove
    /// \param data
    /// WARNING !!! error prone
    void remove (const T &data) {
        T delta_n = (data - m_mean);
        m_mean -= data/m_count;
        if(m_count > 1) m_mean *= m_count/(m_count-1);
        m_M2 -= (data-m_mean)*delta_n;
        --m_count;
    }

    void swap(const T &data, const T& other) {
        T d1 = (data-m_mean);
        m_mean += (other - data)/m_count;
        T d2 = (other-m_mean);
        m_M2 += d2*d2-d1*d1;
    }

    void clear() { *this = incremental_order2(); }

    size_t size() const { return m_count; }

    T mean() const { return m_mean; }

    T variance() const {
        if(m_count < 2)
            return 0;
        else
            return m_M2/(m_count -1);
    }

    T rms() const { return sqrt(variance()); }

    void operator += (const incremental_order2 & other) {
        size_t nx = other.m_count + m_count;
        T d = other.m_mean - m_mean;
        T mx;
        if(m_count > 50 && other.m_count > 50)
            mx = (m_mean*m_count + other.m_mean*other.m_count) /
                    m_count + other.m_count;
        else {
            mx = m_mean + d * other.m_count / nx;
        }
        m_M2 = other.m_M2 + m_M2 + d*d*m_count*other.m_count/nx;
        m_mean = mx;
        m_count = nx;
    }

    template < typename T1 >
    friend incremental_order2 &
    operator << (incremental_order2<T> &st, const T1 &data) {
        st.add(data);
        return st;
    }

};

template <typename T>
class incremental_MA : public incremental_order2<T> {
    std::vector<T> m_data;
    size_t m_pos;
    size_t m_size;
    typedef incremental_order2<T> BaseClass;
public:
    incremental_MA(size_t size = 10) :
        m_pos(0),
        m_data(0),
        m_size(size)
    {}

    void add(const T& data) {
        if(m_data.size() < m_size) {
            m_data.push_back(data);
            BaseClass::add(data);
        } else {
            BaseClass::swap(m_data[m_pos],data);
            m_data[m_pos]=data;
            m_pos = (m_pos+1)%m_size;            
        }
    }

    template < typename T1 >
    friend incremental_MA &
    operator << (incremental_MA<T> &st, const T1 &data) {
        st.add(data);
        return st;
    }
};

template <typename T>
class incremental_MI {
    std::vector<T> m_data;
    T m_sum;
    size_t m_pos;
    size_t m_size;

public:
    incremental_MI(size_t size = 10) :
        m_pos(0),
        m_data(0),
        m_size(size)
    {}

    void add(const T& data) {
        m_sum += data;
        if(m_data.size() <= m_size) {
            m_data.push_back(data);
        } else {
            m_sum -= m_data[m_pos];
            m_data[m_pos]=data;
            m_pos = (m_pos+1)%m_size;
        }
    }


    const T sum(void) { return m_sum; }
    const T operator ()(void) { return m_sum; }

    const size_t size() { return m_data.size(); }

    template < typename T1 >
    friend incremental_MI &
    operator << (incremental_MI<T> &st, const T1 &data) {
        st.add(data);
        return st;
    }
};

} // detail




////////////////////////////////////////////////////////////////////////////////
//  StatisticUtils  ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class StatUtils {
public:
    typedef detail::incremental_order2<double> IncrementalOrder2;
    typedef detail::incremental_MA<double>     MA;
    typedef detail::incremental_MI<double>     MI;

};


#endif // STAITSTICUTILS_H

