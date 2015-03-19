#ifndef LOCKABLE_H
#define LOCKABLE_H


#include "Core/Mutex.h"
#include "Core/AutoLock.h"

////////////////////////////////////////////////////////////////////////////////
//  Lockable  //////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define CCS_LOCK_SCOPE(mutex) AutoLock al(mutex); (void)al

class Lockable
{
public:

    Lockable(const Lockable &) : m_mutex(new Mutex) { }

    Lockable() : m_mutex(new Mutex) {}

    ~Lockable() {
        delete m_mutex;
    }


    void lock() const { m_mutex->lock(); }

    void unlock() const { m_mutex->unlock(); }

    Mutex & mutex() const { return *m_mutex; }

    operator Mutex &() const { return *m_mutex; }

private:
    Mutex *m_mutex;
};



#endif // LOCKABLE_H

