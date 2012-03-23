#include "Mutex.h"
#include "Utility.h"

namespace BaseClient
{

Mutex *Mutex::create()
{
	pthread_mutexattr_t a;
	pthread_mutex_t m;
	
	//set PTHREAD_MUTEX_RECURSIVE in case of deadlock when a thread try to lock a mutex twice.
	//However, other threads would get blocked if they try to lock a mutex already locked by one thread.
	pthread_mutexattr_settype(&a, PTHREAD_MUTEX_RECURSIVE);
	Mutex *pMutex = NULL;
	if(pthread_mutex_init(&m, &a) == 0)
	{	
		pMutex = new Mutex(m);
	}
	pthread_mutexattr_destroy(&a);
	return pMutex;
}
	
void Mutex::destroy(Mutex *m)
{
	C_DELETE(m);
}

Mutex::Mutex(pthread_mutex_t m)
:m_mutex(m)
{
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&m_mutex);
}

void Mutex::lock()
{
	pthread_mutex_lock(&m_mutex);
}

void Mutex::unlock()
{
	pthread_mutex_unlock(&m_mutex);
}

bool Mutex::trylock()
{
	return pthread_mutex_trylock(&m_mutex) == 0;
}

}
