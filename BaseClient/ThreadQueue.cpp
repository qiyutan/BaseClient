//
//  ThreadQueue.cpp
//  BaseClient
//
//  Created by Qiyu Tan on 3/26/12.
//  Copyright (c) 2012 zombuck. All rights reserved.
//

#include "ThreadQueue.h"
#include "ThreadQueueImpl.h"
#include "Thread.h"

namespace BaseClient
{
    
ThreadQueue *ThreadQueue::create(const char *name, int concurrentThreadCount)
{
    return ThreadQueueImpl::create(name, concurrentThreadCount);
}
    
bool ThreadQueue::add(Thread *t)
{
    return t->setQueue(this);
}
    
}
