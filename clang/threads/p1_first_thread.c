#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// pthread functions have to retun a void pointer
// and they take a void pointer as an argument.
void* myturn(void* arg)
{
	for (int i = 0; i < 5; i++)
  {
    sleep(1);
    printf("My Turn! %d\n", i+1);
  }
  return NULL;
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
  pthread_create(&newthread, NULL, myturn, NULL);
  yourturn();
  pthread_join(newthread, NULL);
  return 0;
}
