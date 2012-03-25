#ifndef _BASECLIENT_SEMPHOREPOSIX_H
#define _BASECLIENT_SEMPHOREPOSIX_H

#include "SemaphorePosix.h"

namespace BaseClient
{

class SemaphorePosix : Semaphore
{
public:
	//semphore in system kenerl. used among processes.
	static Semaphore *create(const char *name, unsigned int value);
	static Semaphore *open(const char *name);

	//semphore in shared memory, used among threads.
	static Semaphore *create(unsigned int value);

	//The name will be disassociated with any semaphore, but the semaphore won't be deallocated before all processes call close() to remove references they own.
	static bool unlink(const char *name);

	bool wait();
	bool trywait();
	bool post();
	bool value(int &v);

private:
	Semaphore(se_t s, const char *name = NULL);
	~Semaphore();

private:
	se_t _sem;
	std::string _name;
};

}

#endif
