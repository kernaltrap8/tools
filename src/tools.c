// tools Copyright (C) 2024 kernaltrap8
// This program comes with ABSOLUTELY NO WARRANTY
// This is free software, and you are welcome to redistribute it
// under certain conditions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define help                                                                   \
  "tools Copyright (C) 2024 kernaltrap8\nThis program is licensed under the "  \
  "GNU GPLv3.\n'r' or 'randstring'\n    prints a random string using the "     \
  "characters from the ascii table with the length of 32 chars\n'c' or "       \
  "'countlength'\n    counts the length of a string, passed from stdin\n'p' "  \
  "or printreg\n    prints the value of a register (eax, ebx, ecx, edx, ebp, " \
  "esp, eip)"
#define VERSION "0.2"

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

  printf("%d\n", count);
}

void printreg(char *r) {
  int reg_value;
  // store the value of each register in reg_value then print it
  if (!strcmp(r, "eip")) {
    void *reg_value;
    asm("call next_instruction\nnext_instruction:\npop %0" : "=r"(reg_value));
    printf("%p\n", reg_value);
  } else {
    if (!strcmp(r, "eax")) {
      asm("movl %%eax, %0" : "=r"(reg_value));
    }
    if (!strcmp(r, "ebx")) {
      asm("movl %%ebx, %0" : "=r"(reg_value));
    }
    if (!strcmp(r, "ecx")) {
      asm("movl %%ecx, %0" : "=r"(reg_value));
    }
    if (!strcmp(r, "edx")) {
      asm("movl %%edx, %0" : "=r"(reg_value));
    }
    if (!strcmp(r, "ebp")) {
      asm("movl %%ebp, %0" : "=r"(reg_value));
    }
    if (!strcmp(r, "esp")) {
      asm("movl %%esp, %0" : "=r"(reg_value));
    }
    printf("0x%x\n", reg_value);
  }
}

int main(int argc, char *argv[]) {
  if (argc < 1) {
    printf("No parameters provied.\ntools Copyright (C) 2024 kernaltrap8\n"
           "This program is licensed under the GNU GPLv3.\n");
    return 1;
  }
  if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
    printf("%s", help);
    return 0;
  }
  if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")) {
    printf("tools v%s\n", VERSION);
    return 0;
  }
  if (!strcmp(argv[1], "randstring") || !strcmp(argv[1], "r")) {
    randstring();
    return 0;
  }
  if (!strcmp(argv[1], "countlength") || !strcmp(argv[1], "c")) {
    if (argc < 3) {
      printf("usage: tools countlength <string>\n");
      return 1;
    }
    countlength(argv[2]);
    return 0;
  }
  if (!strcmp(argv[1], "printreg") || !strcmp(argv[1], "p")) {
    printreg(argv[2]);
    return 0;
  } else {
    printf("invalid command %s.\n%s", argv[1], help);
    return 1;
  }

  return 0;
}
