#ifndef TIMER_H
#define TIMER_H


#include <sys/time.h>
#include <ctime>

////////////////////////////////////////////////////////////////////////////////
//  Timer  /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class Timer
{
public:
    void Start() {
        gettimeofday(&m_tstart, NULL);
        m_cstart = std::clock();
    }

    double StopWatch() {
        gettimeofday(&m_tend, NULL);
        m_cend = std::clock();
        return GetRealTime();
    }

    double GetRealTime() const {
        return m_tend.tv_sec - m_tstart.tv_sec +
                (m_tend.tv_usec - m_tstart.tv_usec)*1E-6;
    }

    double GetUserTime() const {
        return static_cast<double>(m_cend-m_cstart) / CLOCKS_PER_SEC;
    }
private:
    std::clock_t m_cstart, m_cend;
    struct timeval m_tstart, m_tend;
};


#endif // TIMER_H

