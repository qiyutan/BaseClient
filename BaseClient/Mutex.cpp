//
//  Mutex.cpp
//  BaseClient
//
//  Created by Qiyu Tan on 3/27/12.
//  Copyright (c) 2012 zombuck. All rights reserved.
//

#include "Mutex.h"
#include "MutexPosix.h"

namespace BaseClient
{
    
Mutex* Mutex::create()
{
    return MutexPosix::create();
}
    
}