#include <stdio.h>
#include <string.h>

unsigned int is_equilibrium;

int is_mobile_equilibrium();
void print_equilibrium();

int main() {
    int nr_test_cases;
    char garbage[10];
    scanf("%d", &nr_test_cases);
    fgets(garbage, sizeof garbage, stdin);
    fgets(garbage, sizeof garbage, stdin);
    while(nr_test_cases--) {
        is_equilibrium = 1;
        is_mobile_equilibrium();
        print_equilibrium();
        if(nr_test_cases != 0) {
            printf("\n");
        }
    }
    return(0);
}

int is_mobile_equilibrium() {
  int wl, dl, wr, dr;
  scanf("%d%d%d%d", &wl, &dl, &wr, &dr);
  if (wl == 0) {
    wl = is_mobile_equilibrium();
  }
  if (wr == 0) {
    wr = is_mobile_equilibrium();
  }
  if (wl * dl != wr * dr) {
    is_equilibrium = 0;
  }
  return wl + wr;
}

void print_equilibrium() {
  if (is_equilibrium) {
    printf("%s\n", "YES");
  } else {
    printf("%s\n", "NO");
  }
}
