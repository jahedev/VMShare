#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

void * thread_start(void * arg)
{
  for (int i = 1; i <= 5; i++)
  {
    sleep(1);
    printf("My Turn! %d.\n", i);
  }

  return NULL;
}

void somefunc()
{
	for(int i = 1; i <= 3; i++)
  {
    sleep(1);
    printf("Your Turn! %d.\n", i);
  }
}



int main()
{
  pthread_t thread;
  int ret;

  
  if ( (ret = pthread_create(&thread, NULL, thread_start, NULL)) ) {
    errno = ret;
    perror("pthread_create");
    return -1;
  }

  somefunc();

  
  if  ( (ret = pthread_join(thread, NULL)) ) {
    errno = ret;
    perror("pthread_join");
    return -1;
  }

  return 0;
}