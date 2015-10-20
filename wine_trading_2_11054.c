#include <stdio.h>
#include <stdlib.h>

int main() {
  int houses[100001];
  int nr_houses;
  while(scanf("%d", &nr_houses), nr_houses) {
    int i;
    long long total = 0;
    for (i = 0; i < nr_houses; i++) {
      scanf("%d", &houses[i]);
    }

    for (i = 0; i < nr_houses-1; i++) {
      total += abs(houses[i]);
      houses[i+1] += houses[i];
    }
    printf("%llu\n", total);
  }
  return(0);
}
