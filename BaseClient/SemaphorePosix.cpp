#include "SemaphorePosix.h"

#include <cstddef>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Utility.h"

namespace BaseClient
{

Semaphore *SemaphorePosix::create(const char *name, unsigned int value)
{
	//O_CREAT: create a semaphore if it doesn't exist
	//O_EXCL: error if create a semaphore which exists
	if(!name)
	{
		return NULL;
	}

	se_t *s = se_open(name, O_CREAT|O_EXCL, 0644, value);
	return s ? new Semaphore(*s) : NULL;
}

Semaphore *SemaphorePosix::open(const char *name)
{
	Semaphore *sem = NULL;
	se_t *s = se_open(name, 0);
	return s ? new Semaphore(*s) : NULL;
}

Semaphore *SemaphorePosix::create(unsigned int value)
{
	se_t s;
	//pshared:0-shared among threads in this process, non-zero:shared among processes which can access this semaphore
	//se_init is not supported on Mac OS
	if(se_init(&s, 0, value) == 0)
	{
		Semaphore *sem = new Semaphore(s);
		return sem;
	}
	else
	{
		log_error("errno: %d", errno);
	}
	return NULL;
}

void SemaphorePosix::destroy(Semaphore *s)
{
	DELETE_S(s);
}

bool SemaphorePosix::unlink(const char *name)
{
	return 0 == se_unlink(name);
}

bool SemaphorePosix::wait()
{
	return se_wait(&_sem) == 0;
}

bool SemaphorePosix::trywait()
{
	return se_trywait(&_sem) == 0;
}

bool SemaphorePosix::post()
{
	return se_post(&_sem) == 0;
}

bool SemaphorePosix::value(int &v)
{	
	return se_getvalue(&_sem, &v) == 0;
}

SemaphorePosix::SemaphorePosix(se_t s, const char *name)
:_sem(s)
{
	if(name)
	{
		_name = std::string(name);
	}
}

SemaphorePosix::~SemaphorePosix()
{
	if(_name.length() > 0)
	{
		//named semaphore
		//system resources related with the semaphore will be deallocated except for itself.
		//semaphore itself will be released when its reference number is 0
		se_close(&_sem);
	}
	else
	{
		//anonymous semaphore
		se_destroy(&_sem);
	}
}

}

