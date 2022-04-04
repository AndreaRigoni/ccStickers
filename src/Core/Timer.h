#ifndef TIMER_H
#define TIMER_H


#include <sys/time.h>
#include <ctime>


////////////////////////////////////////////////////////////////////////////////
//  Timer  /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define TIME_INLINE __attribute__((always_inline))

class Timer
{
public:
    typedef struct timeval TI;
    typedef struct timespec TS;

    Timer() { Start(); }

    void Start() TIME_INLINE {
        m_tvel.tv_sec = 0;
        m_tvel.tv_usec = 0;
        m_tsel.tv_sec = 0;
        m_tsel.tv_nsec = 0;
        gettimeofday(&m_tvs, NULL);
    }

    void Stop()  TIME_INLINE {
        gettimeofday(&m_tve, NULL);
    }

    double StopWatch() TIME_INLINE {
        gettimeofday(&m_tve, NULL);
        return to_s(GetElapsed());
    }

    double StopWatch_ms() TIME_INLINE {
        gettimeofday(&m_tve, NULL);
        return to_ms(GetElapsed());
    }

    void Pause() TIME_INLINE {
        clock_gettime(CLOCK_THREAD_CPUTIME_ID,&m_tss);
    }

    void Resume()  TIME_INLINE {
        clock_gettime(CLOCK_THREAD_CPUTIME_ID,&m_tse);
        m_tsel.tv_sec  = m_tse.tv_sec-m_tss.tv_sec+m_tsel.tv_sec;
        m_tsel.tv_nsec = m_tse.tv_nsec-m_tss.tv_nsec+m_tsel.tv_nsec;
    }

    void PauseAll() TIME_INLINE {
        gettimeofday(&m_tve, NULL);
        m_tvel = GetElapsed();
    }

    void ResumeAll() TIME_INLINE {
        gettimeofday(&m_tvs, NULL);
    }

    TI GetElapsed() TIME_INLINE {
        TI dt;
        dt.tv_sec  = m_tve.tv_sec-m_tvs.tv_sec
                + (m_tvel.tv_sec-m_tsel.tv_sec);
        dt.tv_usec = m_tve.tv_usec-m_tvs.tv_usec
                + (m_tvel.tv_usec-m_tsel.tv_nsec*1E-3);
        return dt;
    }

    double GetElapsed_s() TIME_INLINE {
        return to_s(GetElapsed());
    }

    double GetElapsed_ms() TIME_INLINE {
        return to_ms(GetElapsed());
    }

private:

    static double to_s(const TI &t) TIME_INLINE {
        return t.tv_sec + t.tv_usec*1E-6;
    }

    static double to_ms(const TI &t) TIME_INLINE {
        return t.tv_sec*1E3 + t.tv_usec*1E-3;
    }

    TI m_tvs, m_tve, m_tvel;
    TS m_tss, m_tse, m_tsel;
};


class TimerPause {
    Timer &timer;
public:
    TimerPause(const Timer &t) : timer(const_cast<Timer&>(t)) { timer.Pause(); }
    ~TimerPause() { timer.Resume(); }
private:
    TimerPause(const TimerPause &other) : timer(other.timer) {}
};

#ifndef TIMER_PAUSE
# define TIMER_PAUSE(timer) TimerPause _auto_timer_pause_##timer(timer); (void)_auto_timer_pause_##timer;
#endif


#endif // TIMER_H

