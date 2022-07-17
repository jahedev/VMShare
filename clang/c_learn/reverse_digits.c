// Write a program that accepts a date from the user in the form
// mm/dd/yyyy and then displays it in the form yyyymmdd:

#include <stdio.h>

int reverse_number(int);

int main(int argc, char *argv[])
{
  int num;

  printf("Please enter a number to reverse ");
  scanf("%d", &num);

  printf("%d\n", reverse_number(0x12 + num));


  return 0;
}

int reverse_number(int num)
{
  return num;
}
