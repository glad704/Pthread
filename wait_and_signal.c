/*************************************************************************
 * FILE		: wait_and_signal().c
 * DESCRIPTION	: Program to demonstrate the use wait and signal in pthread.
 * AUTHOR	: GLADSON HANSDA
 * DATED	: 20/07/2020
 * **********************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

pthread_cond_t cv;
pthread_mutex_t lock;

void* thread(void* v)
{
	printf("Locking and waiting. Type unlock to unlock me.\n");
	pthread_mutex_lock(&lock);
	pthread_cond_wait(&cv,&lock);
	printf("I've been unlocked.\n");
	pthread_mutex_unlock(&lock);
	return NULL;
}

int main()
{
	char cmd[1024];
	pthread_t *t;

	printf("Type lock to run a thread that locks and waits.\n");
	printf("Type unlock to unlock the same thread.\n");
	while(fscanf(stdin,"%s",cmd)!=EOF)
	{
		if(strcmp(cmd,"lock")==0)
		{
			t = (pthread_t*)malloc(sizeof(pthread_t));
			pthread_create(t,NULL,thread,NULL);
		}
		else if(strcmp(cmd,"unlock")==0)
		{
			pthread_cond_signal(&cv);
		}
	}
	return 0;
}
