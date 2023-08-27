/**
 * Two different ways to loop over an array of arrays.
 *
 * Spotted at:
 * http://stackoverflow.com/questions/9936132/why-does-the-order-of-the-loops-affect-performance-when-iterating-over-a-2d-arra
 */
#include <stdio.h>
#include <time.h>

void option_one() {
  int i, j;
  static int x[4000][4000];
  for (i = 0; i < 4000; i++) {
    for (j = 0; j < 4000; j++) {
      x[i][j] = i + j;
    }
  }
}

void option_two() {
  int i, j;
  static int x[4000][4000];
  for (i = 0; i < 4000; i++) {
    for (j = 0; j < 4000; j++) {
      x[j][i] = i + j;
    }
  }
}

int main() {
  clock_t start = clock();
  // option_one();
  option_two();
  clock_t end = clock();
  double elapsed = (end - start) / (double) CLOCKS_PER_SEC;
  printf("%0.3g ns per element.\n", elapsed * 1e9 / (4000 * 4000));
  return 0;
}
