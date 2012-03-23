#include <pthread.h>
#include "Noncopyable.h"
#include "Utility.h"
#include "RWLock.h"

namespace BaseClient
{

RWLock *RWLock::create()
{
	pthread_rwlock_t lock;
	if(pthread_rwlock_init(&lock, NULL) == 0)
	{
		return new RWLock(lock);
	}
	return NULL;
}

void RWLock::destroy(RWLock *lock)
{
	C_DELETE(lock);
}

void RWLock::rdlock()
{
	pthread_rwlock_rdlock(&m_lock);
}

bool RWLock::tryrdlock()
{
	return 0 == pthread_rwlock_tryrdlock(&m_lock);
}
void RWLock::wrlock()
{
	pthread_rwlock_wrlock(&m_lock);
}

bool RWLock::trywrlock()
{
	return 0 == pthread_rwlock_trywrlock(&m_lock);
}

void RWLock::unlock()
{
	pthread_rwlock_unlock(&m_lock);
}

RWLock::RWLock(pthread_rwlock_t lock)
:m_lock(lock)
{
}

RWLock::~RWLock()
{
	pthread_rwlock_destroy(&m_lock);
}

}
