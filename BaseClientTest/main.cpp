//
//  main.cpp
//  BaseClientTest
//
//  Created by Qiyu Tan on 3/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "ThreadQueue.h"
#include "Thread.h"

void run(void *str)
{
    for(int i = 0; i < 100; i++){
        std::cout << i << "\t" << (const char*)str << "\n";
    }
}

int main (int argc, const char * argv[])
{

    // insert code here...
    std::cout << "Hello, World!\n";
    BaseClient::ThreadQueue *queue = BaseClient::ThreadQueue::create("Hello");
    for(int i = 0; i < 10; i++){
        BaseClient::Thread *t = BaseClient::Thread::create(run, (void*)"Hello, thread");
        queue->add(t);
    }
    for(;;);
    return 0;
}

