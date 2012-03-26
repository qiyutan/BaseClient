//
//  RWLockPosix.h
//  BaseClient
//
//  Created by Qiyu Tan on 3/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BaseClient_RWLockPosix_h
#define BaseClient_RWLockPosix_h

#include "RWLock.h"
#include <pthread.h>

namespace BaseClient
{

class RWLockPosix : public RWLock
{
public:
    static RWLock *create();
    
    void rlock();
    bool tryRLock();
    void wlock();
    bool tryWLock();
    void unlock();
    
protected:
    RWLockPosix(pthread_rwlock_t lock);
    virtual ~RWLockPosix();
    
private:
    pthread_rwlock_t _lock;
    
};
    
}

#endif
