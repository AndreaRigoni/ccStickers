#ifndef THREAD_H
#define THREAD_H

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


#endif // THREAD_H

