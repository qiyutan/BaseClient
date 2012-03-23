#ifndef _BASECLIENT_RW_LOCK_H
#define _BASECLIENT_RW_LOCK_H

#include <pthread.h>
#include "Noncopyable.h"

namespace BaseClient
{

class RWLock : public Noncopyable
{
public:
    static RWLock *create();
    static void destroy(RWLock *lock);
    
    virtual void rlock() = 0;
    virtual bool tryRLock() = 0;
    virtual void wlock() = 0;
    virtual bool tryWLock() = 0;
    virtual void unlock() = 0;
};

}

#endif
