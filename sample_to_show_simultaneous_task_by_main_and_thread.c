/**************************************************************************
 * FILE		: sample_to_show_simultaneous_task_by_main_and_thread().c
 * DESCRIPTION	: Program to demonstrate simultaneous task by main thread
 * 		  i.e addition of two number and created thread i.e subtraction
 * 		  of two number.
 * AUTHOR	: GALDSON HANSDA
 * DATED	: 20/07/2020
 * ***********************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

void* Addition(void* arg)
{
	sleep(2);
	long sum=0;
	//args = *(long*)arg;
	for(long i=0;i<10;i++)
	{
		sum+=i;
	}
	printf("Addition of these numbers are: %ld\n",sum);
	pthread_exit(NULL);
}
int main()
{
	pthread_t thread;
	int rc;
	long t=0;
	rc = pthread_create(&thread,NULL,Addition,(void*)t);
	if(rc)
	{
		printf("ERROR; return code from pthread_create() is %d\n",rc);
		exit(-1);
	}
	printf("Number from digit 1 to 10 are: \n");
	for(t=0;t<10;t++)
	{
		printf("%ld\n",t);
	}
	pthread_join(thread,NULL);
	pthread_exit(NULL);
	return 0;
}
