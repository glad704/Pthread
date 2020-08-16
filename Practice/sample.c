/************************************************************************
 * FILE		: sample.c
 * DESCRIPTION	: Program to demonstrate the use of pthread
 * AUTHOR	: GLADSON HANSDA
 * DATED	: 04/08/2020
 * *********************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void* wait()
{
	sleep(2);
	printf("Done.\n");
}

int main(void)
{
	pthread_t thread;
	int err;

	err = pthread_create(&thread,NULL,wait,NULL);

	if(err)
	{
		printf("An error occured: %d",err);
		return 1;
	}

	printf("Waiting for the thread to end...\n");
	pthread_join(thread,NULL);

	printf("Thread ended.\n");
	return 0;
}
