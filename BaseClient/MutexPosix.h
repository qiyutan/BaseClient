//
//  MutextPosix.h
//  BaseClient
//
//  Created by Qiyu Tan on 3/24/12.
//  Copyright (c) 2012 zombuck. All rights reserved.
//

#ifndef BaseClient_MutextPosix_h
#define BaseClient_MutextPosix_h

#include "Mutex.h"
#include <pthread.h>

namespace BaseClient{

class MutexPosix : public Mutex 
{
public:
	static Mutex* create();
    
	void lock();
	void unlock();
	bool trylock();
    
protected:
	MutexPosix(pthread_mutex_t m);
    virtual ~MutexPosix();
    
private:
	pthread_mutex_t _mutex;
	
};
    
}

#endif
