/**************************************************************************
 * FILE		: condition_wait_and_signal().c
 * DESCRIPTION	: Program to demonstrate the use of condition, wait and signal.
 * AUTHOR	: GLADSON HANSDA
 * DATED	: 20/07/2020
 * ***********************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

/*Declaration of thread condition variable*/
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;

/*Declaring mutex*/
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int done = 1;

/*Thread function*/
void* foo(void* tid)
{
	long threadid;
	threadid = (long)tid;

	/*acquire a lock*/
	pthread_mutex_lock(&lock);
	if(done==1)
	{
		/*let's wait on condition variable cond1*/
		done = 2;
		printf("I am thread id: #%ld\n",threadid);
		printf("Waiting on condition variable cond1\n");
		pthread_cond_wait(&cond1,&lock);
		printf("Condition variable received by thread id: #%ld\n",threadid);
	}
	else
	{
		printf("I am thread id: #%ld\n",threadid);
		/*Let's signal condition variable cond1*/
		printf("Signaling condition variable cond1\n");
		pthread_cond_signal(&cond1);
		printf("Condition signal sent by thread id: #%ld\n",threadid);
	}

	/*release lock*/
	pthread_mutex_unlock(&lock);
	printf("Returning thread by thread id: #%ld\n",threadid);

	return NULL;
}

/*Driver code*/
int main()
{
	pthread_t tid1,tid2;
	long t=1,p=2;

	/*Create thread 1*/
	pthread_create(&tid1,NULL,foo,(void*)t);

	/*Sleep for 1 sec so that thread 1 would get a chance to run first*/
	sleep(1);

	/*Create thread 2*/
	pthread_create(&tid2,NULL,foo,(void*)p);

	/*wait for the completion of thread 2*/
	pthread_join(tid2,NULL);

	return 0;
}
