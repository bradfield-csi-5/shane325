#include <stdio.h>
#include <stdlib.h>

#define MAXARGS 128

int main() {
	char cmdline[MAXARGS];

	while (1) {
		printf("--> ");
		fgets(cmdline, MAXARGS, stdin);
		if (feof(stdin))
			exit(0);

		printf("%s\n", cmdline);
	}
}
