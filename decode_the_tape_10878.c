#include <stdio.h>
#include <stdlib.h>

int main() {

  char tape_row[20];
  char garbage[20];
  fgets(garbage, sizeof garbage, stdin);
  sscanf(garbage, "%[^\n]", garbage);

  while(fgets(tape_row, sizeof tape_row, stdin)) {
    if (tape_row[0] != '_') {
      char *ptr = tape_row;
      char binary[10];
      int i = 0;
      while (*ptr) {
        if (*ptr == ' ') {
          binary[i] = '0';
          i++;
        } else if (*ptr == 'o') {
          binary[i] = '1';
          i++;
        }
        ptr++;
      }
      char *ptr2;
      long ret = strtol(binary, &ptr2, 2);
      putchar((char)ret);
    }
  }

  return(0);
}
