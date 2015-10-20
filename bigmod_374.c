#include <stdio.h>

int main() {
  int base, exp, mod;
  while (scanf("%d%d%d", &base, &exp, &mod) != EOF){
    base %= mod;
    long long result = 1;
    while (exp > 0) {
      if (exp % 2 == 1) {
        result = (result * base) % mod;
      }
      exp = exp >> 1;
      base = (base * base) % mod;
    }
    printf("%llu\n", result);
  }
  return(0);
}
