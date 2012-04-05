//
//  Event.cpp
//  BaseClient
//
//  Created by Qiyu Tan on 3/26/12.
//  Copyright (c) 2012 zombuck. All rights reserved.
//

#include "Event.h"
#include "EventPosix.h"

namespace BaseClient
{
    
Event *Event::create()
{
    return EventPosix::create();
}
    
}
