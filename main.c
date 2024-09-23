#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: jp [FILE]\n");
		return 1;
	}

	char *fname = argv[1];
	char *s = read_file(fname);

	if (!s) {
		printf("Unable to open %s\n", fname);
		return 1;
	}

	int valid = is_valid_json(s);
	free(s);

	if (valid) {
		printf("Result: valid\n");
		return 0;
	} else {
		printf("Result: invalid\n");
		return 1;
	}
}
