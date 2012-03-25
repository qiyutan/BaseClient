#ifndef _BASECLIENT_MUTEX_H
#define _BASECLIENT_MUTEX_H

#include "Noncopyable.h"

namespace BaseClient
{

class Mutex : public Noncopyable
{
public:
	static Mutex* create();
    
	virtual void lock() = 0;
	virtual void unlock() = 0;
	virtual bool trylock() = 0;
	
};

}
#endif
