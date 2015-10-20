#include <stdio.h>
#include <stdlib.h>

int* scan_inputs(int size);
int get_average(int *v, int size);

int main() {
  int size, set = 0;
  while(scanf("%d", &size), size) {
      set++;
      int i, number_of_moves = 0;
      int *v = scan_inputs(size);
      int average = get_average(v, size);
      for (i = 0; i < size; i++) {
        if (v[i] > average) {
          number_of_moves += (v[i] - average);
        }
      }
      printf("Set #%d\n", set);
      printf("The minimum number of moves is %d.\n\n", number_of_moves);
      free(v);
  }
  return(0);
}

int get_average(int *v, int size) {
  int i, total = 0;
  for (i = 0; i < size; i++) {
    total += v[i];
  }
  return total / size;
}

int* scan_inputs(int size) {
  int i;
  int *v;
  v = malloc(size * sizeof(int));
  for(i=0; i < size; i++)
    scanf("%d", &v[i]);
  return v;
}
