/**
 * Write the function `strindex(s, t)`, which returns the position of the right most
 * occurrence of t in s, or -1 if there is none.
 */
#include <stdio.h>
#include <string.h>

int strindex(char s[], char t);

int main () {

    char s[] = "hello world!";
    char t = 'l';

    printf("%i\n", strindex(s, t));
    return 0;
}

int strindex(char s[], char t) {

    int i = strlen(s) - 1;
    for (; i > 0; i--) {
        if (s[i] == t) {
            return i;
        }
    }
    return -1;
}
