#ifndef _BASECLIENT_SPINLOCK_H
#define _BASECLIENT_SPINLOCK_H

#include "Noncopyable.h"

//on Mac OS, alternative for pthread_spinlock_t is OSSpinLock, defined in <libkern/OSAtomic.h>

namespace BaseClient
{

class SpinLock : public Noncopyable
{
public:
	static SpinLock *create();

	virtual void lock() = 0;
	virtual bool trylock() = 0;
	virtual void unlock() = 0;
};

}

#endif
