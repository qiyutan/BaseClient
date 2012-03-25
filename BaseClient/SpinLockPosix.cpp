#include "SpinLockPosix.h"
#include "Utility.h"

namespace BaseClient
{

SpinLock *SpinLockPosix::create()
{
	pthread_spinlock_t s;
	//pthread_spin_init(pthread_spinlock_t *lock, int pshared);
	if(pthread_spin_init(&s, 0) == 0)
	{
		SpinLock *lock = new SpinLock(s);
		return lock;
	}
	return NULL;
}

void SpinLockPosix::lock()
{
	pthread_spin_lock(&_spinlock);
}

bool SpinLockPosix::trylock()
{
	return 0 == pthread_spin_trylock(&_spinlock);
}

void SpinLockPosix::unlock()
{
	pthread_spin_unlock(&_spinlock);
}

SpinLockPosix::SpinLockPosix(pthread_spinlock_t s)
:_spinlock(s)
{
}

SpinLockPosix::~SpinLockPosix()
{
	pthread_spin_destroy(&_spinlock);
}

}

