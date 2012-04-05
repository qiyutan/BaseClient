//
//  SpinLockMac.cpp
//  BaseClient
//
//  Created by Qiyu Tan on 3/24/12.
//  Copyright (c) 2012 zombuck. All rights reserved.
//
#include "SpinLockMac.h"
#include "Utility.h"

namespace BaseClient
{
    
SpinLock *SpinLockMac::create()
{
    return new SpinLockMac();
}

void SpinLockMac::lock()
{
    OSSpinLockLock(&_spinlock);
}

bool SpinLockMac::trylock()
{
    return OSSpinLockTry(&_spinlock);
}

void SpinLockMac::unlock()
{
    OSSpinLockUnlock(&_spinlock);
}

SpinLockMac::SpinLockMac()
{
    _spinlock = OS_SPINLOCK_INIT;
}

SpinLockMac::~SpinLockMac()
{
    
}
    
}