#include<stdio.h>
#include<pthread.h>

/**
 * Listing 4.2 (thread-create2) Create Two Threads
 */

struct char_print_parms
{
	char character;
	int count;
};

void* char_print(void* parameters)
{
	/* Cast pointer to the right type.*/
	struct char_print_parms* p = (struct char_print_parms*) parameters;
	int i;

	for(i=0;i<p->count;++i)
	{
		fputc(p->character,stderr);
	}
	return NULL;
}

/**
 * Listing 4.3 Revised Main Function for thread-create2.c
 */

int main()
{
	pthread_t thread1_id;
	pthread_t thread2_id;
	struct char_print_parms thread1_args;
	struct char_print_parms thread2_args;

	thread1_args.character = 'x';
	thread2_args.count = 16384;
	pthread_create(&thread1_id,NULL,&char_print,&thread1_args);

	thread2_args.character = '_';
	thread2_args.count = 16384;
	pthread_create(&thread2_id,NULL,&char_print,&thread2_args);

	pthread_join(thread1_id,NULL);
	pthread_join(thread2_id,NULL);

	return 0;
}


