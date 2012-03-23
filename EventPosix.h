#ifndef _BASECLIENT_EVENT_H
#define _BASECLIENT_EVENT_H

#include "Noncopyable.h"
#include <pthread.h>

namespace BaseClient
{

class Event : public Noncopyable
{
public:
	static Event *create();
	static void destroy(Event *);

	void wait();
	bool trywait();
	void post(); 

private:
	Event(pthread_cond_t, pthread_mutex_t);
	~Event();

private:
	pthread_cond_t _cond;
	pthread_mutex_t _mutex;
	bool _flag;
};

}

#endif
