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
#include <stdint.h>
#include <unistd.h>

#define BIG 1000000000UL
uint32_t counter = 0;

// pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* count_to_big(void* arg) {
  for (uint32_t i=0; i < BIG; i++)
  {
    // this is extremely slow for a billion operations
    // pthread_mutex_lock(&lock);
    counter++;
    // pthread_mutex_unlock(&lock);
  }

  return NULL;
}

int main() {
  pthread_t t;
  pthread_create(&t, NULL, count_to_big, NULL);
  count_to_big(NULL);
  pthread_join(t, NULL);
  printf("Done. Counter = %u\n", counter);
}