#ifndef THREAD_H
#define THREAD_H


#include <signal.h>
#include <pthread.h>
#include <iostream>

#include "unique_ptr.h"

#include <Core/Mutex.h>
#include <Core/AutoLock.h>
#include <Core/Lockable.h>
#include <Core/ConditionVar.h>





////////////////////////////////////////////////////////////////////////////////
// THREAD BASE  ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



class Thread
{
    typedef void (* SigActionHandlerT)(int sig, siginfo_t *si, void *args);
public:
    Thread() {}
    virtual ~Thread() {}

    virtual bool StartThread() {
        return (pthread_create(&_thread, NULL, InternalThreadEntryFunc, this) == 0);
    }

    virtual void StopThread() {
        pthread_cancel(_thread);
    }

    virtual void WaitForThreadToExit() {
        (void) pthread_join(_thread, NULL);
    }

    int SetSigAction(int sig, SigActionHandlerT handler) {
        sa.sa_flags = SA_SIGINFO;
        sigemptyset(&sa.sa_mask);
        sa.sa_sigaction = handler;
        if (sigaction(sig, &sa, NULL) == -1) {
            std::cerr << "Error setting sig handler in thread\n";
            return 0;
        }
        return 1;
    }

    void SendSignal(int sig) const { pthread_kill(_thread, sig); }
    static void SendSignal(Thread &th, int sig) { pthread_kill(th, sig); }

    operator pthread_t() {
        return _thread;
    }

protected:
    virtual void InternalThreadEntry() = 0;

private:
    static void * InternalThreadEntryFunc(void * This) {
        ((Thread *)This)->InternalThreadEntry();
        return NULL;
    }

    struct sigaction sa;
    pthread_t _thread;
};






#endif // THREAD_H
