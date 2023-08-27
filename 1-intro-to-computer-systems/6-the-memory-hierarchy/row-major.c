#include <stdio.h>

#define M 3
#define N 3

int sumarrayrows(int a[M][N]);
int sumarraycols(int a[M][N]);

int main () {
  int temp[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };

  printf("Row major: Sum of array is %d.\n", sumarrayrows(temp));
  printf("Col major: Sum of array is %d.\n", sumarraycols(temp));
}

int sumarrayrows (int a[M][N]) {
  int i, j, sum = 0;

  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      sum += a[i][j];
    }
  }

  return sum;
}

int sumarraycols (int a[M][N]) {
  int i, j, sum = 0;

  for (j = 0; j < N; j++) {
    for (i = 0; i < M; i++) {
      sum += a[i][j];
    }
  }

  return sum;
}
