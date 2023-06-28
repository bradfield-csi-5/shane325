#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char **argv) {
    int c;
    int func;

    typedef int (*convert_functions)(int);
    convert_functions convert[2];
    convert[0] = toupper;
    convert[1] = tolower;

    // int (*convert[2])(int) = {toupper, tolower};

    if (argc > 0) {
        if (strcmp(*argv, "./CASE") == 0) {
            func = 0;
        } else {
            func = 1;
        }
    }

    while ((c = getchar()) != EOF) {
        int result = convert[func](c);
        putchar(result);
    }

    return 0;
}
