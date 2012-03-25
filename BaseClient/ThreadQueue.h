//
//  ThreadQueue.h
//  BaseClient
//
//  Created by Qiyu Tan on 3/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BaseClient_ThreadQueue_h
#define BaseClient_ThreadQueue_h

#include "Noncopyable.h"

namespace BaseClient
{

const int kDefaultConcurrentThreadCount = 5;
class Thread;
    
class ThreadQueue : public Noncopyable
{
    friend class Thread;
public:
    static ThreadQueue *create(const char *name, int concurrentThreadCount = kDefaultConcurrentThreadCount);
    static ThreadQueue *getQueue(const char *name);
    virtual bool add(Thread *t) = 0;
    virtual void cancel() = 0;
    
protected:
    virtual void remove(Thread *t) = 0;
};
    
    
}

#endif
