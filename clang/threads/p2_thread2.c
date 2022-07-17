/**
 * @file p2_thread2.c
 * @author Jahed
 * @brief How to pass arguments to and get results from threads. (pthread_create, pthread_join)
 * @version 0.1
 * @date 2022-03-16
 * @link https://www.youtube.com/watch?v=It0OFCbbTJE&list=PL9IEJIKnBJjFZxuqyJ9JqVYmuFZHr7CFM&index=2
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// pthread functions have to retun a void pointer
// and they take a void pointer as an argument.
void * myturn(void * arg)
{
  int *iptr = (int*)malloc(sizeof(int));
  *iptr = 5;
	for (int i = 0; i < 5; i++)
  {
    sleep(1);
    printf("My Turn! i=%d--iptr=%d\n", i+1, *iptr);
    (*iptr)++;
  }
  return iptr;
}

void yourturn()
{
	for(int i = 0; i < 3; i++)
  {
    sleep(1);
    printf("Your Turn! %d\n", i+1);
  }
}

int main()
{
  pthread_t newthread;
  int *result;

  pthread_create(&newthread, NULL, myturn, NULL);
  yourturn();

  pthread_join(newthread, (void*)&result);
  printf("thread's done: *result=%d\n", *result);
  return 0;
}
