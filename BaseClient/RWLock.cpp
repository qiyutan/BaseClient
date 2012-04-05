//
//  RWLock.cpp
//  BaseClient
//
//  Created by Qiyu Tan on 3/27/12.
//  Copyright (c) 2012 zombuck. All rights reserved.
//

#include "RWLock.h"

#include "RWLockPosix.h"

namespace BaseClient
{
    
RWLock *RWLock::create()
{
    return RWLockPosix::create();
}
    
}