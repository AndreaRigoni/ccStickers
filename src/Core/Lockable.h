#ifndef LOCKABLE_H
#define LOCKABLE_H

#include "Core/Mutex.h"
#include "Core/AutoLock.h"
#include "Core/unique_ptr.h"

////////////////////////////////////////////////////////////////////////////////
//  Lockable  //////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



class Lockable
{
public:
    Lockable() : m_mutex(new Mutex) {}

    ~Lockable() {/* delete m_mutex; */}

    Lockable(const Lockable &) : m_mutex(new Mutex) {}
    Lockable & operator = (const Lockable &) {}
    const Lockable & operator = (const Lockable &) const {}

    void lock() const { m_mutex->lock(); }

    void unlock() const { m_mutex->unlock(); }

    Mutex & mutex() const { return *m_mutex; }
    operator Mutex &() const { return *m_mutex; }

private:
    // TODO: move to shared pointer
    unique_ptr<Mutex> m_mutex;
};





#endif // LOCKABLE_H

