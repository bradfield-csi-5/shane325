#include <stdio.h>

#define LOOPS 1000

int main (int argc, char** argv) {
  int i, sum;

  for (i = 0; i <= LOOPS; i++) {
    sum += i;
  }

  printf("%d\n", sum);
  return sum;
}
