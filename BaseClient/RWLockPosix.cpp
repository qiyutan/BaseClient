#include "RWLockPosix.h"
#include "Utility.h"

namespace BaseClient
{

RWLock *RWLockPosix::create()
{
	pthread_rwlock_t lock;
	if(pthread_rwlock_init(&lock, NULL) == 0)
	{
		return new RWLockPosix(lock);
	}
	return NULL;
}

void RWLockPosix::rlock()
{
	pthread_rwlock_rdlock(&_lock);
}

bool RWLockPosix::tryRLock()
{
	return 0 == pthread_rwlock_tryrdlock(&_lock);
}
void RWLockPosix::wlock()
{
	pthread_rwlock_wrlock(&_lock);
}

bool RWLockPosix::tryWLock()
{
	return 0 == pthread_rwlock_trywrlock(&_lock);
}

void RWLockPosix::unlock()
{
	pthread_rwlock_unlock(&_lock);
}

RWLockPosix::RWLockPosix(pthread_rwlock_t lock)
:_lock(lock)
{
}

RWLockPosix::~RWLockPosix()
{
	pthread_rwlock_destroy(&_lock);
}

}
