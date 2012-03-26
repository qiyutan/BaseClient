//
//  ThreadQueueImpl.cpp
//  BaseClient
//
//  Created by Qiyu Tan on 3/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ThreadQueueImpl.h"

#include "Mutex.h"
#include "Thread.h"
#include <map>
#include <algorithm>

namespace BaseClient
{
    
static Mutex *name2ThreadQueueMutex = Mutex::create();
static std::map<std::string, ThreadQueue*> name2ThreadQueues;
typedef std::map<std::string, ThreadQueue*>::const_iterator Name2ThreadQueuesConstIterator;
typedef std::map<std::string, ThreadQueue*>::iterator Name2ThreadQueuesIterator;
    
static void deleteThread(Thread *t)
{
    if(t){
        delete t;
    }
}
    
ThreadQueue *ThreadQueueImpl::create(const char *name, int concurrentThreadCount)
{
    std::string strName = name;
    ThreadQueue *tq = NULL;
    
    name2ThreadQueueMutex->lock();
    
    Name2ThreadQueuesIterator it = name2ThreadQueues.find(strName);
    if(it != name2ThreadQueues.end()){
        tq = it->second;
    }
    else{
        tq = new ThreadQueueImpl(name, concurrentThreadCount);
        name2ThreadQueues[strName] = tq;
    }
    
    name2ThreadQueueMutex->unlock();
    return tq;
}
    
ThreadQueue *ThreadQueueImpl::getQueue(const char *name)
{
    std::string strName = name;
    ThreadQueue *tq = NULL;
    
    name2ThreadQueueMutex->lock();
    
    Name2ThreadQueuesIterator it = name2ThreadQueues.find(strName);
    if(it != name2ThreadQueues.end()){
        tq = it->second;
    }
    
    name2ThreadQueueMutex->unlock();
    return tq;
}
    
ThreadQueueImpl::ThreadQueueImpl(const char *name, int concurrentThreadCount)
    :_name(name),
    _concurrentThreadCount(concurrentThreadCount)
{
    _mutex = Mutex::create();
}
    
ThreadQueueImpl::~ThreadQueueImpl()
{
    name2ThreadQueueMutex->lock();
    name2ThreadQueues.erase(_name);
    name2ThreadQueueMutex->unlock();
    delete _mutex;
}
    
bool ThreadQueueImpl::add(Thread *t)
{
    if(ThreadQueue::add(t)){
        _mutex->lock();
        if(_runningThreads.size() < _concurrentThreadCount){
            t->start();
            _runningThreads.insert(t);
        }
        else{
            _waitingThreads.push_back(t);
        }
        _mutex->unlock();
        return true;
    }
    return false;
}
    
void ThreadQueueImpl::cancel()
{
    _mutex->lock();
    
    std::for_each(_runningThreads.begin(), _runningThreads.end(), deleteThread);
    std::for_each(_waitingThreads.begin(), _waitingThreads.end(), deleteThread);
    
    _mutex->unlock();
}
    
void ThreadQueueImpl::remove(Thread *t)
{
    _mutex->lock();
    
    std::set<Thread*>::iterator it = _runningThreads.find(t);
    if(it != _runningThreads.end()){
        delete *it;
        _runningThreads.erase(it);
        if(!_waitingThreads.empty()){
            Thread *nextThread = _waitingThreads.front();
            _waitingThreads.pop_front();
            _runningThreads.insert(nextThread);
            nextThread->start();
        }
    }
    else{
        std::deque<Thread*>::iterator it2 = std::find(_waitingThreads.begin(), _waitingThreads.end(), t);
        if(it2 != _waitingThreads.end()){
            delete *it2;
            _waitingThreads.erase(it2);
        }
    }
    
    _mutex->unlock();
}
    
}