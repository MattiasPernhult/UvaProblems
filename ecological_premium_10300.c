#include <stdio.h>
#include <stdlib.h>

int* scan_three_inputs();

int main() {
  int nr_test_cases;
  int nr_farmers;
  scanf("%d\n", &nr_test_cases);

  while(nr_test_cases) {
    scanf("%d\n", &nr_farmers);
    float total = 0;
    int i;
    for (i = 0; i < nr_farmers; i++) {
      int *v = scan_three_inputs();
      float size_of_farm = v[0], nr_animals = v[1], environment = v[2];
      total = total + (((size_of_farm / nr_animals) * environment) * nr_animals);
      free(v);
    }
    printf("%d\n", (int)total);
    nr_test_cases--;
  }
  return(0);
}

int* scan_three_inputs() {
  int i, size = 3;
  int *v;
  v = malloc(size * sizeof(int));
  for(i=0; i < size; i++)
    scanf("%d", &v[i]);
  return v;
}
