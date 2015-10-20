#include <stdio.h>
#include <string.h>

int main() {
  char first[2000000], second[2000000];
  while (scanf("%s %s", first, second) == 2) {
    int i = 0, j = 0, first_length = strlen(first), second_length = strlen(second), length = 0;
    for (j = 0; j < second_length; j++) {
      if (first[i] == second[j]) {
        length++;
        i++;
      }
    }
    if (first_length == length) {
      printf("%s\n", "Yes");
    } else {
      printf("%s\n", "No");
    }
  }
  return(0);
}
