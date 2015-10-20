#include <stdio.h>
#include <limits.h>

int inputMatrix[11][110];
int sumMatrix[11][110];
int pathMatrix[11][110];
int inputRow, inputColumn, way, current, number;

int main(){
  int column, row, i;
  while (scanf("%d%d", &inputRow, &inputColumn) != EOF){
    for (row = 0; row < inputRow; row++){
      for (column = 0; column < inputColumn; column++){
        scanf("%d", &number);
        inputMatrix[row][column] = number;
        if (column == (inputColumn - 1)){
          sumMatrix[row][column] = number;
        }
        pathMatrix[row][column] = 0;
      }
    }

    for (column = inputColumn - 2; column >= 0; column--){
      for (row = 0; row < inputRow; row++){
        current = INT_MAX;
        int ways[] = {row-1, row, row+1};
        for (i = 0; i < 3; i++){
          way = (ways[i] + inputRow) % inputRow;

          if(sumMatrix[way][column+1] < current || (sumMatrix[way][column+1] == current && way < pathMatrix[row][column])) {
            current = sumMatrix[way][column+1];
            pathMatrix[row][column] = way;
          }
        }
        sumMatrix[row][column] = inputMatrix[row][column] + current;
      }
    }

    int x = 0, sum = 0, choose = INT_MAX;
    for (row = 0; row < inputRow; row++){
      if (sumMatrix[row][0] < choose){
        choose = sumMatrix[row][0];
        x = row;
      }
    }

    printf("%d", x+1);

    for (column = 0; column < inputColumn-1; column++){
      sum += inputMatrix[x][column];
      x = pathMatrix[x][column];
      printf(" %d", x+1);
    }

    sum += inputMatrix[x][inputColumn-1];

    printf("\n%d\n", sum);
  }
  return(0);
}
