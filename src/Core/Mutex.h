#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

////////////////////////////////////////////////////////////////////////////////
//  Mutex  /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class Mutex {
public:
    Mutex() {
        _create();
    }

    ~Mutex() {
        _destroy();
    }

    bool lock() {
        _try_lock();
    }

    void unlock() {
        _unlock();
    }

private:
    pthread_mutex_t mutex;
    void _create() { pthread_mutex_init(&mutex, NULL); }
    void _lock() { pthread_mutex_lock(&mutex); }
    bool _try_lock() { pthread_mutex_trylock(&mutex); }
    void _unlock() { pthread_mutex_unlock(&mutex); }
    void _destroy() { pthread_mutex_destroy(&mutex); }
};



#endif // MUTEX_H

