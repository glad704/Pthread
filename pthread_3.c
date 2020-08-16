#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sysexits.h>

#define DIM 2

/**
 * 4.1.4 More on Thread IDs
 */

pthread_t tid[DIM];

void* dosomething(void* arg)
{
	pthread_t id = pthread_self();

	if(pthread_equal(id,tid[0]))
	{
		printf("First thread processing\n");
	}
	else
	{
		printf("Second thread processing\n");
	}
	return NULL;
}

int main()
{
	int i,err;

	for(i=0;i<DIM;i++)
	{
		err = pthread_create(&(tid[i]),NULL,&dosomething,NULL);
		if(err!=0)
		{
			fprintf(stderr,"Can't create thread. Reason: '%s'",strerror(err));
			exit(EX_OSERR);
		}
		else
		{
			printf("Thread create successfully\n");
		}
	}

	for(i=0;i<DIM;i++)
	{
		pthread_join(tid[i],NULL);
	}

	return 0;
}
