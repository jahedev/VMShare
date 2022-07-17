/*
 *  Mohammed Hossain
 *  CISC 3320
 *  Homework 1
 *  File Name: psfork.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void print_process_info(char *p_name);

int main()
{
  pid_t fork_pid;

  fork_pid = fork();

  if (fork_pid > 0)	// grandparent
  {
    print_process_info("grandparent");

    fork_pid = wait(NULL);
    if (fork_pid == -1)
    {
      perror("wait error in grandparent process.");
    }
  }
  else if (fork_pid == 0)	// parent
  {
    fork_pid = fork();

    if (fork_pid > 0)	// parent
    {
      print_process_info("parent");

      fork_pid = wait(NULL);
      if (fork_pid == -1)
      {
        perror("wait error in parent process.");
      }
      else
      {
        exit(0);
      }
    }
    else if (fork_pid == 0)	// grandchild
    {
      print_process_info("grandchild");
      exit(0);
    }
    else	// error: fork_pid == -1
    {
      perror("fork error in parent process");
    }
  }
  else	// error: fork_pid == -1
  {
    perror("fork error in grandparent process");
  }
}

void print_process_info(char *p_name)
{
  printf("I am the %s process with a PID of %d.\n", p_name, getpid());
}