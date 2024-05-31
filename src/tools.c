#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define help                                                                   \
  "tools Copyright (C) 2024 kernaltrap8\nThis program is licensed under the "  \
  "GNU GPLv3.\n'r' or 'randstring'\n    prints a random string using the "     \
  "characters from the ascii table with the length of 32 chars\n'c' or "       \
  "'countlength'\n    counts the length of a string, passed from stdin\n"

void randstring(void) {
  int length = 32;
  srand(time(NULL));
  char str[length];

  for (int i = 0; i < length; i++) {
    str[i] = rand() % (126 - 32) + 32;
  }

  str[length] = '\0';
  printf("%s\n", str);
}

void countlength(char *string) {
  char *str = string;
  int count = 0;

  for (int i = 0; str[i] != '\0'; i++) {
    count++;
  }

  printf("%d", count);
}

int main(int argc, char *argv[]) {
  if (argc < 1) {
    printf("No parameters provied.\ntools Copyright (C) 2024 kernaltrap8\n"
           "This program is licensed under the GNU GPLv3.\n");
  }
  if (!strcmp(argv[1], "--help")) {
    printf("%s", help);
  }
  if (!strcmp(argv[1], "randstring") || !strcmp(argv[1], "r")) {
    randstring();
  }
  if (!strcmp(argv[1], "countlength") || !strcmp(argv[1], "c")) {
    countlength(argv[2]);
  }

  return 0;
}
