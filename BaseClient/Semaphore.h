#ifndef _BASECLIENT_SEMPHORE_H
#define _BASECLIENT_SEMPHORE_H

#include <semaphore.h> 
#include <string>
#include "Noncopyable.h"

namespace BaseClient
{

class Semaphore : public Noncopyable
{
public:
	//semphore in system kenerl. used among processes.
	static Semaphore *create(const char *name, unsigned int value);
	static Semaphore *open(const char *name);

	//semphore in shared memory, used among threads.
	static Semaphore *create(unsigned int value);

	//The name will be disassociated with any semaphore, but the semaphore won't be deallocated before all processes call close() to remove references they own.
	static bool unlink(const char *name);

	virtual bool wait() = 0;
	virtual bool trywait() = 0;
	virtual bool post() = 0;
	virtual bool value(int &v) = 0;
};

}

#endif
