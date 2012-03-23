#ifndef _BASECLIENT_THREAD_H
#define _BASECLIENT_THREAD_H

#include "Noncopyable.h"

namespace BaseClient
{

#define ThreadObject void*
typedef bool(*ThreadFunction)(ThreadObject);
typedef uint32_t ThreadId_t;

typedef enum
{
    kThreadPriorityLow = 1,
    kThreadPriorityDefault,
    kThreadPriorityHigh,
    kThreadPriorityHighest,
    kThreadPriorityRealtime
}ThreadPriority;
    
#define kThreadMaxNameLength 64

class Thread : public Noncopyable
{
public:
    
    //Factory method
    static Thread* create(ThreadFunction func = 0, 
                          ThreadObject obj= 0, 
                          ThreadPriority priority = kThreadPriorityDefault, 
                          const char* threadName = 0);
    
    //Get current kenerl thread id
    static ThreadId_t getThreadId();
    
    virtual bool start(ThreadId_t &threadId) = 0;
    virtual void makeUnalive() = 0;
    
    virtual bool setAffinity(const int *processorNumbers, const unsigned int amountOfProcessors) {
        return false;
    }
    
    virtual bool cancel() = 0;
};

}

#endif
