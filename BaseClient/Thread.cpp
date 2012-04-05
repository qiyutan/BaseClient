//
//  Thread.cpp
//  BaseClient
//
//  Created by Qiyu Tan on 3/26/12.
//  Copyright (c) 2012 zombuck. All rights reserved.
//

#include "Thread.h"
#include "ThreadPosix.h"
#include "ThreadQueue.h"

namespace BaseClient
{

Thread *Thread::create(ThreadFunction func, 
                       ThreadObject obj, 
                       ThreadPriority priority, 
                       const char* threadName)
{
    return ThreadPosix::create(func, obj, priority, threadName);
}
    
bool Thread::start()
{
    ThreadId_t t;
    return start(t);
}

bool Thread::setQueue(ThreadQueue *q)
{
    if(!_threadQueue){
        _threadQueue = q;
        return true;
    }
    return false;
}
    
void Thread::afterRun()
{
    if(_threadQueue){
        _threadQueue->remove(this);
    }
}
    
}
