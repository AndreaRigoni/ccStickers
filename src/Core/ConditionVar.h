#ifndef CONDITION_VAR_H
#define CONDITION_VAR_H

#include <pthread.h>


class ConditionVar {
public:
    ConditionVar() { _create(); }
    ~ConditionVar() { _destroy(); }
    void wait() { _wait(); }
    bool waitTimeout(size_t msec) { return _waitTimeout(msec); }
    void notify() { _notify(); }

private:
    pthread_mutex_t mutex;
    pthread_cond_t condition;

    void _create() {
        pthread_mutex_init(&mutex,NULL);
        pthread_cond_init(&condition, NULL);
    }

    void _wait() {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&condition, &mutex);
        pthread_mutex_unlock(&mutex);
    }

    bool _waitTimeout(size_t msec) {
        timespec t;
        clock_gettime(CLOCK_REALTIME, &t);
        t.tv_sec += msec / 1000L;
        t.tv_nsec += msec % 1000L * 1000000L;
        pthread_mutex_lock(&mutex);
        bool res =  pthread_cond_timedwait(&condition, &mutex, &t) == 0 ? true:false;
        pthread_mutex_unlock(&mutex);
        return res;
    }

    void _notify() {
        pthread_mutex_lock(&mutex);
        pthread_cond_broadcast(&condition);
        pthread_mutex_unlock(&mutex);
    }

    void _destroy() {
        pthread_cond_destroy(&condition);
    }
};


#endif // CONDITION_VAR_H
