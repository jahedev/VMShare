#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>

// define functions
int str_contains_text(char *str, char *text);
void *grep_file(void *arg);
int grep_line(char *line, char *text, char *message);

char *text;                                       // will hold user specified text to search
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // to synchronize threads

// global count variables
int total_lines_scanned = 0;
int total_lines_matched = 0;

int main(int argc, char *argv[])
{
  // argv[1]: text to search for
  // argv[2..n]: files in which text will be searched
  if (argc < 3)
  {
    printf("Error: You must enter at least one filename, and one pattern.\n");
    exit(EXIT_FAILURE);
  }

  text = argv[1];

  // will hold a thread for every filename specified by user
  pthread_t t1[argc - 2];

  // to keep track of current thread index
  int i = 0;

  // create threads to grep, for each filename specified
  for (int argi = 2; argi < argc; argi++)
  {
    pthread_create(&(t1[i]), NULL, &grep_file, argv[argi]);
    i++;
  }

  // join all threads of pthread_t t1
  for (i = 0; i < argc - 2; i++)
  {
    // 2nd arg is NULL because we handle line count inside of the
    // grep_file function, so we do not require return value.
    pthread_join(t1[i], NULL);
  }

  printf("Total of %d lines matched of %d scanned.\n", total_lines_matched, total_lines_scanned);
  return EXIT_SUCCESS;
}

/*
 * Used to search if a string contains another string
 *
 * Returns 1 if text is found in string.
 * Returns 0 if NOT found.
 */
int str_contains_text(char *str, char *text)
{
  int len = strlen(str);
  for (int i = 0; i < len; i++)
  {
    int letters_matched = 0;

    if (str[i] == text[0])
    {
      int text_len = strlen(text);
      int tmp_i = i;
      for (int j = 0; j < text_len && tmp_i < len; j++)
      {
        if (text[j] == str[tmp_i])
          letters_matched++;
        if (letters_matched >= text_len)
          return 1;
        tmp_i++;
      }
    }
  }
  return 0;
}

// for a specified string filename, open that file
// and grep all the lines that match 'text' string.
//
// called by pthread_create()
void *grep_file(void *arg)
{
  pthread_mutex_lock(&lock);

  char *filename = (char *)arg;

  int fd = open(filename, O_RDONLY);
  if (fd == -1)
  {
    printf("Error: Couldn't open %s.\n", filename);
    exit(EXIT_FAILURE);
  }

  int ret;                   // return value of read()
  char *line = malloc(4096); // used to contain line until '\n'
  char *buffer = malloc(2);  // used to contain a single chraacter read
  int index = 0;             // current index of line string

  // counts for this specific file
  int line_count = 0;
  int lines_matched = 0;

  // make sure we can read file
  ret = read(fd, buffer, 1);
  if (ret == -1)
  {
    printf("Error: reading file.");
    exit(EXIT_FAILURE);
  }

  // read file until the end
  while (ret != 0 && ret != -1)
  {
    line[index++] = buffer[0];

    // if the current charaacter is a newline, we will end the line
    // and then run grep_line() on it
    if (*buffer == '\n')
    {
      line[--index] = '\0';
      line_count++;
      // printf("Line: %s\n", line);
      if (grep_line(line, text, filename))
        lines_matched++;

      memset(line, 0, sizeof(line)); // reset line string
      index = 0;                     // reset index
    }

    // read next character
    ret = read(fd, buffer, 1);
  }

  // end and grep the final line
  line[index] = '\0';
  line_count++;
  if (grep_line(line, text, filename))
    lines_matched++;

  printf("-- END %s: %d/%d TOTAL MATCHED LINES --\n\n", filename, lines_matched, line_count);

  total_lines_scanned += line_count;
  total_lines_matched += lines_matched;

  pthread_mutex_unlock(&lock);

  free(line);
  free(buffer);

  pthread_exit(0);
  return NULL;
}

// greps a string and prints it out if it matches
int grep_line(char *line, char *text, char *message)
{
  if (str_contains_text(line, text))
  {
    printf("%s: %s\n", message, line);
    return 1;
  }
  return 0;
}