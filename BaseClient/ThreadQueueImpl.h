//
//  ThreadQueueImpl.h
//  BaseClient
//
//  Created by Qiyu Tan on 3/26/12.
//  Copyright (c) 2012 zombuck. All rights reserved.
//

#ifndef BaseClient_ThreadQueueImpl_h
#define BaseClient_ThreadQueueImpl_h

#include "ThreadQueue.h"
#include <deque>
#include <set>
#include <string>

namespace BaseClient
{
    
class Thread;
class Mutex;
    
class ThreadQueueImpl : public ThreadQueue
{
public:
    static ThreadQueue *create(const char *name, int concurrentThreadCount = kDefaultConcurrentThreadCount);
    static ThreadQueue *getQueue(const char *name);
    virtual ~ThreadQueueImpl();
    
    bool add(Thread *t);
    void cancel();
   
    
protected:
    ThreadQueueImpl(const char *name, int concurrentThreadCount);
    void remove(Thread *t);
    
private:
    Mutex *_mutex;
    std::set<Thread*> _runningThreads;
    std::deque<Thread*> _waitingThreads;
    std::string _name;
    int _concurrentThreadCount;
    
};

    
}

#endif
