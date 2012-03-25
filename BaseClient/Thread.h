#ifndef _BASECLIENT_THREAD_H
#define _BASECLIENT_THREAD_H

#include "Noncopyable.h"
#include <stdint.h>
#include <stddef.h>

namespace BaseClient
{

#define ThreadObject void*
typedef void(*ThreadFunction)(ThreadObject);
typedef uint32_t ThreadId_t;
const size_t kDefaultStackSize = 4*1024*1024;

typedef enum
{
    kThreadPriorityLow = 1,
    kThreadPriorityDefault,
    kThreadPriorityHigh,
    kThreadPriorityHighest,
    kThreadPriorityRealtime
}ThreadPriority;
    
#define kThreadMaxNameLength 64
class ThreadQueue;
class Thread : public Noncopyable
{
    friend class ThreadQueue;
    
public:
    
    //Factory method
    static Thread* create(ThreadFunction func = 0, 
                          ThreadObject obj= 0, 
                          ThreadPriority priority = kThreadPriorityDefault, 
                          const char* threadName = 0);
    
    //Get current kenerl thread id
    static ThreadId_t getThreadId();
    bool start();
    virtual bool start(ThreadId_t &threadId) = 0;
    virtual bool cancel() = 0;
    virtual bool isAlive() = 0;
    
private:
    virtual bool setQueue(ThreadQueue *q) = 0;
    
private:
    ThreadQueue *_threadQueue;
};

}

#endif
