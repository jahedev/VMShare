#include <stdio.h>

int main(void) {
  printf("hello, world.\n");
  int num;
  char str[50];
  scanf("%d%s", &num, str);
  printf("You entered: %d and %s\n", num, str);
}

