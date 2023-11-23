#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
void* thread1_main(void *arg);
void* thread2_main(void *arg);

int main(int argc, char *argv[]) 
{
   pthread_t t1_id;
   pthread_t t2_id;

   int thread1_param = 5;
   int thread2_param = 5;

   
   if(pthread_create(&t1_id, NULL, thread1_main, (void*)&thread1_param)!=0)
   {
      puts("pthread_create() error");
      return -1;
   };    

   if(pthread_create(&t2_id, NULL, thread2_main, (void*)&thread2_param)!=0)
   {
      puts("pthread_create() error");
      return -1;
   };

	pthread_join(t1_id, NULL);
	pthread_join(t2_id, NULL);
    sleep(3);  
    // pthread_join(t1_id, NULL);
	// pthread_join(t2_id, NULL);
   
   puts("end of main");
   return 0;
}

void* thread1_main(void *arg) 
{
   int i;
   int cnt=*((int*)arg);
   for(i=0; i<cnt; i++)
   {
      sleep(1);  puts("running thread...2");    
   }
   return NULL;
}

void* thread2_main(void *arg)
{
   int i;
   int cnt=*((int*)arg);
   for(i=0; i<cnt; i++)
   {
      sleep(1);  puts("running thread...1");    
   }
   return NULL;
}
