#include "Event.h"
#include "../common/util.h"

namespace qy
{

Event *Event::create()
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	Event *e = NULL;
	if(pthread_mutex_init(&mutex, NULL) == 0)
	{
		if(pthread_cond_init(&cond, NULL) == 0)
		{
			e = new Event(cond, mutex);
		}
		else
		{
			pthread_mutex_destroy(&mutex);
		}
	}
	return e;
}

void Event::destroy(Event *e)
{
	delete_null(e);
}

Event::Event(pthread_cond_t cond, pthread_mutex_t mutex)
:m_cond(cond), m_mutex(mutex), m_flag(false)
{
	
}

Event::~Event()
{
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&m_cond);
}

void Event::wait()
{
	pthread_mutex_lock(&m_mutex);
	while(!m_flag)
	{
		//1, unlock m_mutex
		//2, if m_cond is signaled, start to lock m_mutex again
		//m_count may be changed before, so it needs to be check again after m_mutex locked
		//e.g. two threads A, B are waiting,  m_count is 1. A locks m_mutex, B waits to lock m_mutex. A change m_count to be 0.
		//so B needs to check m_count again after it lock m_mutex.
		//To be conceded, this wouldn't happen here. because in Event::post, pthread_cond_signal is called instead of pthread_cond_broadcast.
		//The former only signal one waiting thread instead of all.
		pthread_cond_wait(&m_cond, &m_mutex);
	}
	m_flag = true;
	pthread_mutex_unlock(&m_mutex);
}

bool Event::trywait()
{
	pthread_mutex_lock(&m_mutex);
	if(!m_flag)
	{
		pthread_mutex_unlock(&m_mutex);
		return false;
	}
	m_flag = false;
	pthread_mutex_unlock(&m_mutex);
	return true;
}

void Event::post()
{
	pthread_mutex_lock(&m_mutex);
	m_flag = true;
	pthread_mutex_unlock(&m_mutex);
	pthread_cond_signal(&m_cond);
}

}

