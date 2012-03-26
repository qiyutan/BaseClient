#ifndef _BASECLIENT_RW_LOCK_H
#define _BASECLIENT_RW_LOCK_H

#include "Noncopyable.h"

namespace BaseClient
{

class RWLock : public Noncopyable
{
public:
    static RWLock *create();
    
    virtual void rlock() = 0;
    virtual bool tryRLock() = 0;
    virtual void wlock() = 0;
    virtual bool tryWLock() = 0;
    virtual void unlock() = 0;
};

}

#endif
