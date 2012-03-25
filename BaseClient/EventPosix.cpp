#include "EventPosix.h"
#include "Utility.h"

namespace BaseClient
{

Event *EventPosix::create()
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	EventPosix *e = NULL;
	if(pthread_mutex_init(&mutex, NULL) == 0){
		if(pthread_cond_init(&cond, NULL) == 0){
			e = new EventPosix(cond, mutex);
		}
		else{
			pthread_mutex_destroy(&mutex);
		}
	}
	return e;
}

void EventPosix::destroy(Event *e)
{
	DELETE_S(e);
}

EventPosix::EventPosix(pthread_cond_t cond, pthread_mutex_t mutex)
:_cond(cond), _mutex(mutex), _flag(false)
{
	
}

EventPosix::~EventPosix()
{
	pthread_mutex_destroy(&_mutex);
	pthread_cond_destroy(&_cond);
}

void EventPosix::wait()
{
	pthread_mutex_lock(&_mutex);
	while(!_flag){
		//1, unlock _mutex
		//2, if _cond is signaled, start to lock _mutex again
		//_count may be changed before, so it needs to be check again after _mutex locked
		//e.g. two threads A, B are waiting,  _count is 1. A locks _mutex, B waits to lock _mutex. A change _count to be 0.
		//so B needs to check _count again after it lock _mutex.
		//To be conceded, this wouldn't happen here. because in EventPosix::post, pthread_cond_signal is called instead of pthread_cond_broadcast.
		//The former only signal one waiting thread instead of all.
		pthread_cond_wait(&_cond, &_mutex);
	}
	_flag = true;
	pthread_mutex_unlock(&_mutex);
}

bool EventPosix::trywait()
{
	pthread_mutex_lock(&_mutex);
	if(!_flag){
		pthread_mutex_unlock(&_mutex);
		return false;
	}
	_flag = false;
	pthread_mutex_unlock(&_mutex);
	return true;
}

void EventPosix::post()
{
	pthread_mutex_lock(&_mutex);
	_flag = true;
    pthread_cond_broadcast(&_cond);
	pthread_mutex_unlock(&_mutex);
}

}

