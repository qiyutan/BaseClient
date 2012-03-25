//
//  ThreadPosix.cpp
//  BaseClient
//
//  Created by Qiyu Tan on 3/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ThreadPosix.h"

#include <errno.h>
#include <string.h> // strncpy
#include <time.h>   // nanosleep
#include <unistd.h>

#ifdef WEBRTC_LINUX
#include <sys/types.h>
#include <sched.h>
#include <sys/syscall.h>
#include <linux/unistd.h>
#include <sys/prctl.h>
#endif

#if defined(__MACH__)
#include <mach/mach.h>
#endif

#include "Event.h"
#include "Utility.h"

namespace BaseClient
{
    
    
const int kSchedulePolicy = SCHED_FIFO;
    
void* ThreadPosix::startThread(void *threadObj)
{
    static_cast<ThreadPosix*>(threadObj)->run();
    return 0;
}
    
Thread* ThreadPosix::create(ThreadFunction func, ThreadObject obj, ThreadPriority prio, const char* threadName)
{
    ThreadPosix* ptr = new ThreadPosix(func, obj, prio, threadName);
    if (!ptr)
    {
        return NULL;
    }
   
    if (ptr->init() == false)
    {
        delete ptr;
        return NULL;
    }
    return ptr;
}
    
ThreadId_t ThreadPosix::getThreadId() 
{
    return reinterpret_cast<ThreadId_t>(pthread_self());
}
    
ThreadPosix::ThreadPosix(ThreadFunction func, ThreadObject obj, ThreadPriority prio, const char* threadName)
:   _func(func), 
    _obj(obj),
    _priority(prio),
    _pid(-1),
    _thread(0),
    _name(threadName)
{
    
}
    
bool ThreadPosix::init()
{
    int result = 0;
    result = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    CHECK_R(result == 0);
    result = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    CHECK_R(result == 0);
    result = pthread_attr_init(&_attr);
    CHECK_R(result == 0);
    
    return true;
}
    
ThreadPosix::~ThreadPosix()
{
    if(isAlive()){
        cancel();
    }
    pthread_attr_destroy(&_attr);
}
    
bool ThreadPosix::start(ThreadId_t &threadId)
{
    if(!_func){
        return false;
    }
    
    int result  = pthread_attr_setdetachstate(&_attr, PTHREAD_CREATE_DETACHED);
    result = pthread_attr_setstacksize(&_attr, kDefaultStackSize);
    CHECK_R(result == 0);
    result = pthread_create(&_thread, &_attr, startThread, this);
    CHECK_R(result == 0);
    
#if defined (CLIENT_MAC) || defined (CLIENT_IOS)
    threadId = pthread_mach_thread_np(_thread);
#else
    threadId = (ThreadId_t)_thread;
#endif
    
    sched_param param;
    const int minPriority = sched_get_priority_min(kSchedulePolicy);
    const int maxPriority = sched_get_priority_max(kSchedulePolicy);
    if(minPriority < 0 || maxPriority < 0){
        return true;
    }
    
    switch (_priority){
        case kThreadPriorityLow:
            param.sched_priority = minPriority + 1;
            break;
        case kThreadPriorityDefault:
            param.sched_priority = (minPriority + maxPriority) / 2;
            break;
        case kThreadPriorityHigh:
            param.sched_priority = maxPriority - 3;
            break;
        case kThreadPriorityHighest:
            param.sched_priority = maxPriority - 2;
            break;
        case kThreadPriorityRealtime:
            param.sched_priority = maxPriority - 1;
            break;
    }
    
    pthread_setschedparam(_thread, kSchedulePolicy, &param);
    return true;
}
    
bool ThreadPosix::cancel()
{
    if(pthread_cancel(_thread) == 0){
        _thread = 0;
        return true;
    }
    return false;
}

bool ThreadPosix::isAlive()
{
    return 0 == pthread_kill(_thread, 0);
}
    
void ThreadPosix::run()
{
    _func(_obj);
}
    
}