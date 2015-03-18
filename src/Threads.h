#ifndef TREADS_H
#define TREADS_H

#include <pthread.h>


////////////////////////////////////////////////////////////////////////////////
// THREAD BASE  ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class Thread
{
public:
   Thread() {}
   virtual ~Thread() {}

   bool StartThread() {
      return (pthread_create(&_thread, NULL, InternalThreadEntryFunc, this) == 0);
   }

   void StopThread() {
       pthread_cancel(_thread);
   }

   void WaitForThreadToExit() {
      (void) pthread_join(_thread, NULL);
   }

protected:
   virtual void InternalThreadEntry() = 0;

private:
   static void * InternalThreadEntryFunc(void * This) {
       ((Thread *)This)->InternalThreadEntry();
       return NULL;
   }

   pthread_t _thread;
};



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

    void lock() {
        _lock();
    }

    void unlock() {
        _unlock();
    }

private:
    pthread_mutex_t mutex;
    void _create() { pthread_mutex_init(&mutex, NULL); }
    void _lock() { pthread_mutex_lock(&mutex); }
    void _unlock() { pthread_mutex_unlock(&mutex); }
    void _destroy() { pthread_mutex_destroy(&mutex); }
//#elif defined (MDS_WINDOWS)
//    HANDLE mutex;
//    void _create() { mutex = CreateMutex(NULL, FALSE, NULL); }
//    void _lock() { WaitForSingleObject(mutex, INFINITE); }
//    void _unlock() { ReleaseMutex(mutex); }
//    void _destroy() { CloseHandle(mutex); }
//#endif
};



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




////////////////////////////////////////////////////////////////////////////////
//  Lockable  //////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define MDS_LOCK_SCOPE(mutex) AutoLock al(mutex); (void)al

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







#endif // TREADS_H

