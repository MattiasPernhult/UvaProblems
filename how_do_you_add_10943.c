#include <stdio.h>

int graph[102][102];

void calculate_graph() {
  int i, j;
  for (j = 1; j <= 100; j++){
    graph[1][j] = j;
  }
  for (i = 1; i <= 100; i++) {
    graph[i][1] = 1;
  }
  for (i = 2; i <= 100; i++){
    for (j = 2; j <= 100; j++){
      int sum = graph[i][j-1] + graph[i-1][j];
      graph[i][j] = sum % 1000000;
    }
  }
}

int main() {
  calculate_graph();
  int n, k;
  while (scanf("%d%d", &n, &k), n) {
    printf("%d\n", graph[n][k]);
  }
  return(0);
}
