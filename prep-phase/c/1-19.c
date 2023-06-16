/*
 * Exercise 1-19
 * Write a function `reverse(s)` that reverses the character
 * string s. Use it to write a program that reverses its input a line at a time
 * */
#include <stdio.h>

#define MAXLINE 1000 /* Max input line size */

int get_line(char l[], int maxline);
void reverse(char s[], int size);

int main() {
    int len;
    char line[MAXLINE];

    while((len = get_line(line, MAXLINE)) > 0) {
        reverse(line, len);
        printf("%s", line);
    }

    return 0;
}

int get_line(char l[], int limit) {
    int c, i;

    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        l[i] = c;
    }
    if (c == '\n') {
        l[i] = c;
        i++;
    }
    l[i] = '\0';

    return i;
}

void reverse(char line[], int size) {
    int start = 0;
    int end = size - 1;
    char temp;

    if (line[end] == '\n') {
        end--;
    }

    while (start < end) {
        temp = line[start];
        line[start] = line[end];
        line[end] = temp;
        start++;
        end--;
    }
}
