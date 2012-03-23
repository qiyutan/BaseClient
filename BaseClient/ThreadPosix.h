#ifndef _BASECLIENT_THREADPOSIX_H
#define _BASECLIENT_THREADPOSIX_H

#include "Thread.h"
#include <pthread.h>
#include <unistd.h>
#include <string>

namespace BaseClient
{

class Event;
    
class ThreadPosix : public Thread
{
public:
    //Factory method
    static Thread* create(ThreadFunction func = 0, 
                          ThreadObject obj= 0, 
                          ThreadPriority priority = kThreadPriorityDefault, 
                          const char* threadName = 0);
    
    //Get current kenerl thread id
    static ThreadId_t getThreadId();
    
    bool start(ThreadId_t &threadId);
    void makeUnalive();
    bool setAffinity(const int *processorNumbers, const unsigned int amountOfProcessors);    
    bool cancel();
    
    void run();
    
protected:
    ThreadPosix(ThreadFunction func, ThreadObject obj, ThreadPriority prio, const char* threadName);
    bool init();
    virtual ~ThreadPosix();
    
private:
    ThreadFunction _func;
    ThreadObject _obj;
    
    // internal state
    bool                    _alive;
    bool                    _dead;
    ThreadPriority          _priority;
    Event                   *_event;
    
    // zero-terminated thread name string
    std::string     _name;
    bool                    _setThreadName;
    
    pid_t                   _pid;
    pthread_attr_t          _attr;
    pthread_t               _thread;
    
};

}

#endif
