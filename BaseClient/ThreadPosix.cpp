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

namespace BaseClient
{
extern "C"
{
    static void* startThread(void *threadObj)
    {
        static_cast<ThreadPosix*>(threadObj)->run();
        return 0;
    }
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
    
ThreadPosix::ThreadPosix(ThreadFunction func, ThreadObject obj, ThreadPriority prio, const char* threadName)
: _func(func), 
    _obj(obj),
    _alive(false),
    _dead(true),
    _priority(prio),
    _pid(-1),
    _attr(), 
    _thread(0),
    _name(threadName)
{
}
    
ThreadId_t ThreadPosix::getThreadId() 
{
    return reinterpret_cast<ThreadId_t>(pthread_self());
}
    
bool ThreadPosix::init()
{
    int result = 0;
    
    result = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    if (result != 0){
        return false;
    }
    result = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    if (result != 0){
        return false;
    }
    result = pthread_attr_init(&_attr);
    if (result != 0){
       return false;
    }
}
    
ThreadPosix::~ThreadPosix()
{
    pthread_attr_destroy(&_attr);
    delete _event;
}