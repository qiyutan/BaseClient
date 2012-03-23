#ifndef _BASECLIENT_EVENT_H
#define _BASECLIENT_EVENT_H

#include "Noncopyable.h"

namespace BaseClient
{

class Event : public Noncopyable
{
public:
	static Event *create();
	static void destroy(Event *);

	virtual void wait() = 0;
	virtual bool trywait() = 0;
	virtual void post() = 0; 
};

}

#endif
