/**************************************************************************
 * FILE		: mutex_sig_wait().c
 * DESCRIPTION	: Program to demonstrate use of mutex,signal and wait.
 * AUTHOR	: GLADSON HANSDA
 * DATED	: 21/07/2020
 * ***********************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define NUM_THREADS 5
#define MAX_COUNT 10

/*create thread argument struct for thr_func()*/
typedef struct _thread_data_t
{
	int tid;
	double stuff;
}thread_data_t;

/*shared data between threads*/
double shared_x;
pthread_mutex_t lock_t;
pthread_cond_t cond;

int count;

void* thr1_func1(void* arg)
{
	pthread_mutex_lock(&lock_t);
	printf("Thread 2: They invoked me\n");

	while(count!=MAX_COUNT)
	{
		pthread_cond_signal(&cond);
		printf("Thread 2: I am still here\n");
		count++;
		pthread_cond_wait(&cond,&lock_t);
	}

	pthread_mutex_unlock(&lock_t);
	printf("Thread 2: I left\n");
	pthread_exit(NULL);
}

void* thr2_func2(void* arg)
{
	pthread_mutex_lock(&lock_t);
	printf("Thread 1: They invoked me\n");

	/*some code here that does interesting stuff and modifies count*/
	while(count!=MAX_COUNT)
	{
		pthread_cond_wait(&cond,&lock_t);
		printf("Thread 1: I am still here");
		count++;
		pthread_cond_signal(&cond);
	}

	pthread_mutex_unlock(&lock_t);
	printf("Thread 1: I left\n");
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t thr1,thr2;
	int rc;
	count=0;

	if((rc = pthread_create(&thr2,NULL,thr2_func2,NULL)))
	{
		fprintf(stderr,"error: pthread_create, rc: %d\n",rc);
		return EXIT_FAILURE;
	}

	if((rc = pthread_create(&thr1,NULL,thr1_func1,NULL)))
	{
		fprintf(stderr,"error: pthread_create, rc: %d\n",rc);
		return EXIT_FAILURE;
	}

	printf("I do something\n");
	pthread_join(thr1,NULL);
	printf("I do something else\n");
	count = MAX_COUNT;
	pthread_cond_signal(&cond);
	printf("Before pthread_join\n");

	/*block until all threads complete*/
	pthread_join(thr2,NULL);
	printf("After pthread_join\n");
	return 0;
}
