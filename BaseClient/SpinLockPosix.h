#ifndef _BASECLIENT_SPINLOCKPOSIX_H
#define _BASECLIENT_SPINLOCKPOSIX_H

#include <pthread.h>
#include "SpinLock.h"

namespace BaseClient
{

class SpinLockPosix : public SpinLock
{
public:
	SpinLock *create();

	void lock();
	bool trylock();
	void unlock();

private:
	SpinLockPosix(pthread_spinlock_t s);
	~SpinLockPosix();

private:
	pthread_spinlock_t _spinlock;


};

}

#endif
