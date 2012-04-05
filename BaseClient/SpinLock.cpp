//
//  SpinLock.cpp
//  BaseClient
//
//  Created by Qiyu Tan on 3/27/12.
//  Copyright (c) 2012 zombuck. All rights reserved.
//

#include "SpinLock.h"

#if defined (__MACH__)
#include "SpinLockMac.h"
#else 
#include "SpinLockPosix.h"
#endif

namespace BaseClient
{
    
SpinLock *SpinLock::create()
{
#if defined (__MACH__)
    return SpinLockMac::create();
#else
    return SpinLockPosix::create();
#endif
}
    
}