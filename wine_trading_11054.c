#include <stdio.h>
#include <stdlib.h>

int main() {
  int nr_houses;
  while(scanf("%d", &nr_houses), nr_houses){
    long long total = 0, pos_total = 0, neg_total = 0;
    int i, house;
    for (i = 0; i < nr_houses; i++) {
      scanf("%d", &house);
      if (house > 0) {
        pos_total += house;
      } else if(house < 0) {
        neg_total += abs(house);
      }
      total += abs(pos_total - neg_total);
    }
    printf("%llu\n", total);
  }
  return(0);
}
