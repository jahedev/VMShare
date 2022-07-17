#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // instantiating strings //

  // allocated in the stack; can read and write
  // char str[] = {'H', 'e', 'l', 'l', 'o', '!', '\0'};
  char str[] = "Hello!";
  printf("%s\n", str); // Hello!

  // allocated its own memory (that might be read only)
  // char *str = "Hello!";
  // const static char noname[] = "Hello!"; char *str = noname;

  // if you want it to be modifiable
  // char *str = malloc(50 * sizeof(char));
  // strcpy (str, "Hello!");
  // free(str);
  

  // changing a character
  str[4] = 'a';
  printf("%s\n", str); // Hella!


  // Array of Strings //

  char array[3][50]; // 3 strings, 50 chars each
  strcpy(array[0], "ABC");
  strcpy(array[1], "DEF");
  strcpy(array[2], "GHI");
  printf("%s %s %s.\n", array[0], array[1], array[2]);






  return 0;
}