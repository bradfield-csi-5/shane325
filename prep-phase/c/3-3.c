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
int should_expand(char input[], int i);

int main() {
    char input[] = "-xa-z0-9";
    char output[200];
    char s, e;
    int i;

    s = e = 0;
    i = 0;
    while (i < strlen(input)) {

        if (input[i] == '-' && should_expand(input, i)) {
            expand(output, input[i-1], input[i+1]);
        } else {
            int j = strlen(output);
            output[j] = input[i];
        }
        i++;
    }

    printf("%s\n", output);

    return 0;
}

void expand(char output[], char s, char e) {

    int i = strlen(output);
    s++;
    e--;
    while (s <= e) {
        output[i] = s;
        s++;
        i++;
    }
}

int should_expand(char input[], int i) {
    char s, e;
    s = input[i-1];
    e = input[i+1];

    if (s < e && (islower(s) && islower(e)) || (isupper(s) && isupper(e)) || (isdigit(s) && isdigit(e))) {
        return 1;
    }

    return 0;
}
