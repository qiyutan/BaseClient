//
//  SpinLockMac.h
//  BaseClient
//
//  Created by Qiyu Tan on 3/24/12.
//  Copyright (c) 2012 zombuck. All rights reserved.
//

#ifndef BaseClient_SpinLockMac_h
#define BaseClient_SpinLockMac_h

#include <libkern/OSAtomic.h>
#include "SpinLock.h"
//on Mac OS, alternative for pthread_spinlock_t is OSSpinLock, defined in <libkern/OSAtomic.h>

namespace BaseClient
{
    
class SpinLockMac : public SpinLock
{
public:
    static SpinLock *create();
    
    void lock();
    bool trylock();
    void unlock();
    
protected:
    SpinLockMac();
    virtual ~SpinLockMac();
    
private:
    OSSpinLock _spinlock;
    
    
};
    
}

#endif
