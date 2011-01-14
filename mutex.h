/*
 *  mutex.h
 *  MonteCarloThread
 */



#ifndef _MUTEX_H
#define _MUTEX_H

#include <pthread.h>

class Mutex
{
public:
	Mutex();
	~Mutex();
	
	
	void Lock();
	void UnLock();
	
	
private:
	pthread_mutex_t  m_mutex;
};

#endif	// _MUTEX_H
	
