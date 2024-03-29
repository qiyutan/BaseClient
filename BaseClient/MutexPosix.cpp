#include "MutexPosix.h"
#include "Utility.h"

namespace BaseClient
{

Mutex *MutexPosix::create()
{
	pthread_mutexattr_t a;
	pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutexattr_init(&a);
	//set PTHREAD_MUTEX_RECURSIVE in case of deadlock when a thread try to lock a mutex twice.
	//However, other threads would get blocked if they try to lock a mutex already locked by one thread.
	pthread_mutexattr_settype(&a, PTHREAD_MUTEX_RECURSIVE);
	Mutex *pMutex = NULL;
    int ret = pthread_mutex_init(&m, &a);
	if(ret == 0)
	{	
		pMutex = new MutexPosix(m);
	}
	pthread_mutexattr_destroy(&a);
	return pMutex;
}

MutexPosix::MutexPosix(pthread_mutex_t m)
:_mutex(m)
{
}

MutexPosix::~MutexPosix()
{
	pthread_mutex_destroy(&_mutex);
}

void MutexPosix::lock()
{
	pthread_mutex_lock(&_mutex);
}

void MutexPosix::unlock()
{
	pthread_mutex_unlock(&_mutex);
}

bool MutexPosix::trylock()
{
	return pthread_mutex_trylock(&_mutex) == 0;
}

}
