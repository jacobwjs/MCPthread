/*
 *  thread.cpp
 *  MonteCarloThread
 *
 */
#include "debug.h"
#include "thread.h"


void *execThread(void *arg);



Thread::Thread()
{
#ifdef DEBUG
	cout << "Contructing thread...\n";
#endif
}

Thread::~Thread()
{
#ifdef DEBUG	
	cout << "Destructing thread...\n";
#endif
}


void Thread::launch()
{	
#ifdef DEBUG
	cout << "Creating pthread...\n";
#endif
	int ret;
	//if ((ret = pthread_create(&t_id, NULL, &Thread::exec, this)) != 0) {
	if ((ret = pthread_create(&t_id, NULL, &execThread, this)) != 0) {
		cout << strerror(ret) << endl;
		//throw "Error creating thread!";
	}
}


void Thread::join()
{
	pthread_join(t_id, NULL);
}


void Thread::exit()
{
	pthread_exit((void *) 0);
}


void *Thread::exec(void *t)
{
#ifdef DEBUG
	cout << "Executing thread...\n";
#endif	
	reinterpret_cast<Thread *> (t)->run();
	return NULL;
}

void *execThread(void *t)
{
#ifdef DEBUG
	cout << "Executing thread part deux...\n";
#endif	
	reinterpret_cast<Thread *> (t)->run();
	return NULL;
}



	