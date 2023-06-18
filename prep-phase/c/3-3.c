/**
 * Exercise 3-3
 * Write a function expand(s1, s2) that expands shorthand notations
 * like "a-z" into long form "abcd....xyz".
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFFER 200

void expand(char output[], char s, char e);

int main() {
    char input[] = "-A-Z0-9";
    char output[200];
    char s, e, c;
    int i;

    s = e = 0;
    i = 0;
    while (i < strlen(input)) {
        c = input[i];
        if (isalnum(c) && !s) {
            s = c;
        } else if (isalnum(c) && !e) {
            e = c;
        }

        if (s && e) {
            expand(output, s, e);
            s = e = 0;
        }
        i++;
    }

    printf("%s\n", output);

    return 0;
}

void expand(char output[], char s, char e) {

    int i = strlen(output);
    while (s <= e) {
        output[i] = s;
        s++;
        i++;
    }
}
