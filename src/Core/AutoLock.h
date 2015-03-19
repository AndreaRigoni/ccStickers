#ifndef AUTOLOCK_H
#define AUTOLOCK_H

#include "Core/Mutex.h"

////////////////////////////////////////////////////////////////////////////////
//  Autolock  //////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class AutoLock {
public:
    AutoLock(Mutex & mutex): mutex(mutex) {
        mutex.lock();
    }

    ~AutoLock() {
        mutex.unlock();
    }

private:
    Mutex & mutex;

};




#endif // AUTOLOCK_H

