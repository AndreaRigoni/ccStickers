
#ifndef PROGRESS_OUTPUT_H
#define PROGRESS_OUTPUT_H

#include <Core/Named.h>

////////////////////////////////////////////////////////////////////////////////
//  PROGRESS OUTPUT  ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class ProgressOutput : public Named {

public:
    ProgressOutput(size_t size = 0, const char *msg = "Completed: ") :
        Named(msg),
        m_expected_count(size),
        m_expected_time_sec(0),
        m_count(0)
    { time(&m_starttime); }

    void SetExpectedCount(size_t count) { this->m_expected_count = count; }
    void SetExpectedTime(float time) { this->m_expected_time_sec = time; }

    float Completed(int cycles = 1) {
        m_count+=cycles;
        float pos = 100.*m_count/m_expected_count;
        time_t now; time(&now);
        float eta = (static_cast<float>(m_expected_count)/m_count-1)*difftime(now,m_starttime);

        if(m_expected_time_sec > 0) {
            float pos_time = 100.*difftime(now,m_starttime)/m_expected_time_sec;
            // if pos and pos_time differ by 20% then use pos_time
            //            if( fabs(pos_time-pos) > 20 ) {
            pos = pos_time;
            eta = m_expected_time_sec - difftime(now,m_starttime);
            //            }
        }

        // fix possible wrong values //
        pos = pos > 100 ? 100 : pos;
        eta = eta > 0 ? eta : 0;

        if(m_expected_count) {
            std::cout << this->GetName()
                      << (int)pos << " %"
                      << " (eta: " << eta_tostring(eta) << ")"
                      << std::endl << std::flush;
            return pos;
        }
        else return 0;
    }

    size_t GetExpectedCount() const { return m_expected_count; }
private:

    static std::string eta_tostring(float eta_s) {
        std::stringstream ss;
        int d = (int)floor(eta_s/3600/24); eta_s = fmod(eta_s,3600*24);
        int h = (int)floor(eta_s/3600); eta_s = fmod(eta_s,3600);
        int m = (int)floor(eta_s/60); eta_s = fmod(eta_s,60);
        int s = (int)floor(eta_s);
        if(d) ss << d << "d:";
        if(d || h) ss << h << "h:";
        if(d || h || m) ss << m << "m:";
        ss << s << "s";
        return ss.str();
    }

    size_t m_expected_count;
    size_t m_count;
    time_t m_starttime;
    float  m_expected_time_sec;
};

#endif // PROGRESS_OUTPUT_H
