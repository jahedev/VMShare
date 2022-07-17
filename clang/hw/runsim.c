#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // isdigit(int c)
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CHILDREN 2000

typedef enum
{
  M_NO_ARGUMENTS,
  M_NON_INTEGER,
  M_INVALID_RANGE
} Messages;

void message(Messages, int);

int main(int argc, char *argv[])
{
  // Variables
  int max_active_processes;
  int running_processes = 0;
  char *buf = malloc(MAX_CHILDREN);

  int fd[2];
  pipe(fd);

  // Exit program if no arguments
  if (argc < 2)
    message(M_NO_ARGUMENTS, 1);

  if (!isdigit(*argv[1]))
    message(M_NON_INTEGER, 1);
  else
    max_active_processes = atoi(argv[1]);

  if (max_active_processes < 1 || max_active_processes > MAX_CHILDREN)
    message(M_INVALID_RANGE, 1);

  // parent process will always be 1
  // child processes will all always be 0
  int id = 1;

  while (fgets(buf, MAX_CHILDREN, stdin))
  {
    buf[strlen(buf) - 1] = '\0';
    // printf("%s\n", buf);

    if (running_processes >= max_active_processes)
    {
      printf("Too many proccesses are already running. (%d)\n", running_processes);
      int child_pid = wait(NULL);
      if (id != child_pid)
      {
        running_processes--;
      }
    }
    else
    {

      id = fork();
      running_processes++;
    }
    // Child processes should not iterate through this while loop
    if (id == 0)
      break;
  }

  // Call exec() if it is a child process
  if (id == 0 && buf != NULL)
  {
    printf("Executing %s...\n", buf);
    execv(buf, "");
  }

  // Print PID upon Exit
  if (id == 0)
  {
    printf("Child PID: %d\n", getpid());
  }
  else
    printf("Parent PID: %d\n", getpid());

  sleep(3);

  free(buf);

  if (id == 0)
    puts("Finished execution!\n");

  running_processes--;
  return 0;
}

void message(Messages m, int exit_with_failure)
{
  switch (m)
  {
  case M_NO_ARGUMENTS:
    puts("Error: No arguments were specified.");
    break;
  case M_NON_INTEGER:
    puts("Error: First argument for maximum processes must be an integer.");
    break;
  case M_INVALID_RANGE:
    printf("Error: Number of processes must be at least 1, upto %d.\n", MAX_CHILDREN);
    break;
  }

  if (exit_with_failure)
    exit(EXIT_FAILURE);
}