#ifndef _BASECLIENT_EVENTPOSIX_H
#define _BASECLIENT_EVENTPOSIX_H

#include <pthread.h>
#include "Event.h"

namespace BaseClient
{

class EventPosix : public Event
{
public:
	static Event *create();

	void wait();
	bool trywait();
	void post(); 

protected:
	EventPosix(pthread_cond_t, pthread_mutex_t);
	~EventPosix();

private:
	pthread_cond_t _cond;
	pthread_mutex_t _mutex;
	bool _flag;
};

}

#endif
