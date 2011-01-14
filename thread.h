/*
 *  thread.h
 *  MonteCarloThread
 */

#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

class Thread
{
public:
	Thread();
	~Thread();

	// Create the thread and call run.
	void launch();
	
	// Join the thread.
	void join();
	
	// Where all the magic happens.
	virtual void run() = 0;
	
	// Return thread_id.
	unsigned long int getThreadID() {return (unsigned long int)t_id;}
	
	
	
protected:
	static void *exec(void *t);
	
	
private:
	pthread_t t_id;
	
	// Prevent copying or assignment;
	Thread(const Thread *arg);
	Thread & operator=(const Thread &rhs);
	
};

#endif	// THREAD_H
