#include <stdio.h>
#include <pthread.h>

static void* thread_main(void*);

int main()
{
	pthread_t t_id = 0ul;
	int thread_parameter = 10;
	int state = pthread_create(&t_id,NULL, thread_main, (void*)&thread_parameter);
	if(state != 0)
	{
		puts("THEARD error() \r\n");
		return 0;
	}
	sleep(10);
	puts("Ending\r\n");
	return 0;
}

void* thread_main(void* arg)
{
	int value = *((int*)arg);
	for(int i = 0; i < value; ++i)
	{
		sleep(1);
		puts("Theading running\r\n");
	}
	return 0;
}

