#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    printf("Error: You must enter an executable and time in seconds.\n");
    exit(EXIT_FAILURE);
  }

  // the standard output is to a terminal,
  // we will change it to my_nohup.txt
  if (isatty(1))
  {
    puts("my_nohup: ignoring input and appending output to 'my_nohup.txt'");
    freopen("my_nohup.txt", "w", stdout);
  }

  // the standard error is to a terminal,
  // we will change it to /tmp/my_nohup_error.txt
  if (isatty(2))
  {
    freopen("/tmp/my_nohup_error.txt", "w", stderr);
  }

  char filepath[1000]; // path of file to execute
  char *args[argc];    // arguments for file to execute

  pid_t child_pid;  // forked child process
  int child_status; // forked child process status

  struct sigaction sa; // to modify signal behavior

  // get old disposition of SIGHUP
  if (sigaction(SIGHUP, NULL, &sa) == -1)
  {
    perror("Could not obtain old disposition for SIGHUP");
    exit(1);
  }

  // if sa_handler is the default one, change it to SIG_IGN to ignore
  // SIGHUP and SIGQUIT
  if (sa.sa_handler == SIG_DFL)
  {
    sa.sa_handler = SIG_IGN;
    if (sigaction(SIGHUP, &sa, NULL) == -1)
    {
      perror("Could not ignore SIGHUP");
      exit(1);
    }

    if (sigaction(SIGQUIT, &sa, NULL) == -1)
    {
      perror("Could not ignore SIGQUIT");
      exit(1);
    }
  }

  // put the arguments of the executable to a args[]
  for (int i = 1; i < argc; i++)
  {
    args[i - 1] = argv[i];
  }
  args[argc - 1] = NULL;

  // set path of executable
  filepath[0] = '\0';
  strcat(filepath, "./");
  strcat(filepath, argv[1]);

  // fork process and execv the executable with arguments
  child_pid = fork();

  if (child_pid == -1) // error
  {
    perror("There was an error forking.");
    return -1;
  }
  else if (child_pid == 0) // forked process
  {
    if (execv(filepath, args) == -1)
    {
      perror("There was an error executing the binary.");
      exit(EXIT_FAILURE);
    }
    exit(0);
  }
  else // parent process
  {
    if (waitpid(child_pid, &child_status, 0) == -1)
    {
      perror("Error on waitpid!");
      return -1;
    }
  }

  // free memory, close streams
  fclose(stdout);
  fclose(stderr);

  // 6 second timeout to test SIGQUIT
  // sleep(6);
  return child_status;
}
