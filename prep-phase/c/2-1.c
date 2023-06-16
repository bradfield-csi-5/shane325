#include <stdio.h>

/**
 * Write a program to determine the range of an `int` variable
 */
int main() {

    int i, j;
    for (i = 0, j = 1; j > i; i++, j++) {
        ;
    }

    printf("%d\n", i);

    return 0;
}
