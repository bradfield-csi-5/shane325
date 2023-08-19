#include <stdint.h>
#include <stdio.h>

int main () {
  uint64_t x = 1L << 32;
  printf("%llu\n", x);
}
