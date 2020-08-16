/*************************************************************************
 * FILE		: another_wait_signal().c
 * DESCRIPTION	: Program to demonstrate wait and signal in pthread.
 * AUTHOR	: GLADSON HANSDA
 * DATED	: 20/07/2020
 * **********************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

int data_ready = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;

void* consumer(void* notused)
{
	printf("In consumer thread...\n");
	while(1)
	{
		pthread_mutex_lock(&mutex);
		while(!data_ready)
		{
			pthread_cond_wait(&condvar,&mutex);
		}

		/*Process data*/
		printf("consumer: got data from producer\n");
		data_ready = 0;
		pthread_cond_signal(&condvar);
		pthread_mutex_unlock(&mutex);
	}
}

void* producer(void* notused)
{
	printf("In producer thread...\n");
	while(1)
	{
		/*Get data from hardware*/
		/*We'll simulate this with a sleep(1)*/

		sleep(1);
		printf("producer: got data from h/w\n");
		pthread_mutex_lock(&mutex);
		while(data_ready)
		{
			pthread_cond_wait(&condvar,&mutex);
		}
		data_ready = 1;
		pthread_cond_signal(&condvar);
		pthread_mutex_unlock(&mutex);
	}
}

int main()
{
	pthread_t tid1,tid2;
	printf("Starting comsumer/producer example...\n");

	/*Create the producer and consumer threads*/
	pthread_create(&tid1,NULL,producer,NULL);
	pthread_create(&tid2,NULL,consumer,NULL);

	/*Let the threads run for a bit*/
	sleep(20);

	return 0;
}
