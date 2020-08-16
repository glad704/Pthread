/**************************************************************************
 * FILE		: passing_address_of_arg().c
 * DESCRIPTION	: Program to demonstrate creation of thread by passing address
 * 		  of args.
 * AUTHOR	: GLADSON HANSDA
 * DATED	: 20/07/2020
 * ***********************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#define NUM_THREADS 8

void* PrintHello(void* threadid)
{
	long taskid;
	sleep(1);
	taskid = *(long*)threadid;
	printf("Hello from thread %ld\n",taskid);
	pthread_exit(NULL);
}

int main()
{
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;
	for(t=0;t<NUM_THREADS;t++)
	{
		rc = pthread_create(&threads[t],NULL,PrintHello,(void*)&t);
		if(rc)
		{
			printf("ERROR; return code from pthread_create() is %d\n",rc);
			exit(-1);
		}
	}
	pthread_exit(NULL);
	return 0;
}
