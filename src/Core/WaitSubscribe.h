#ifndef WAIT_SUBSCRIBE_H
#define WAIT_SUBSCRIBE_H

#include <Lockable.h>
#include <ConditionVar.h>


class WaitSubscriptions : public Lockable {
public:

    WaitSubscriptions(const size_t subscriptor_to_wait = 0, size_t timeout_msec = 0) :
        m_subscriptors(subscriptor_to_wait),
        m_count(0),
        m_timeout_msec(timeout_msec)
    { }

    WaitSubscriptions(const WaitSubscriptions &o) : Lockable(o) {}

    ~WaitSubscriptions() { }

    bool Subscribe() {
        if(!m_subscriptors) return false;
        {
            CCS_LOCK_SCOPE(*this);
            m_count += 1;
            if(m_count >= m_subscriptors) {
                ClearCount();
                m_condition.notify();
                return true;
            }
        }
        if(m_timeout_msec > 0)
            return m_condition.waitTimeout(m_timeout_msec);
        else
            m_condition.wait();
        return true;
    }

    void ClearCount() { m_count = 0; }

private:
    size_t  m_subscriptors;
    size_t  m_count;
    size_t  m_timeout_msec;
    ConditionVar m_condition;
};

#endif // WAIT_SUBSCRIBE_H
