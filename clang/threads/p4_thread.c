#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <semaphore.h>

#define NUM_ITERATIONS 10
#define true 1
#define false 0

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("usage - %S [STUFF TO WRITE]", argv[0]);
    return -1;
  }

  char *block = attach_memory_block(FILENAME, BLOCK_SIZE);
  if (block == NULL) {
    printf("Error: couldn't get block\n");
    return -1;
  }

  while (true) {
    if (strlen(block) > 0) {
      printf("Reading: \"%s\"\n", block);
      int done = (strcmp(block, "quit") == 0);
      block[0] == 0;
      if (done) { break; }
    }
  }

  for (int i = 0; i < NUM_ITERATIONS; i++) {
    printf("Writing: \"%s\n", argv[1]);
    strncpy(block, argv[1], BLOCK_SIZE);
  }

  detach_memory_block(block);

  return 0;
}