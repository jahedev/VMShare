// Write a program that accepts a date from the user in the form
// mm/dd/yyyy and then displays it in the form yyyymmdd:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check_date(char*);
void format_date(char*);
void swap(int, int, char*);

int main(int argc, char *argv[])
{
  char *date = malloc(256);

  printf("Please enter a date (mm/dd/yyyy): ");
  scanf("%s", date);
  printf("You entered: %s -- in yyyymmdd format, it is:\n", date);
  if (check_date(date)) format_date(date);
  printf("%s\n", date);


  return 0;
}

int check_date(char* date) {
  // 1. should be 10 characters
  if (strlen(date) != 10) return 0;

  // 2. there should be 2 slashes
  if (date[2] != '/' || date[5] != '/') return 0;
  
  // 3. the rest of the characters should be digits
  for (int i = 0; i < strlen(date); i++)
  {
    if (i == 2 || i == 5) continue;
    if (!isdigit(date[i])) return 0;
  }

  return 1;
}

void format_date(char* date)
{
  char year[] = {date[6], date[7], date[8], date[9], '\0'};
  char month[] = {date[0], date[1], '\0'};
  char day[] = {date[3], date[4], '\0'};

  char new_date[10];

  strcat(new_date, year);
  strcat(new_date, month);
  strcat(new_date, day);

  strcpy(date, new_date);
}

void swap(int i, int j, char* str)
{
  char tmp = str[i];
  str[i] = str[j];
  str[j] = tmp;
}
