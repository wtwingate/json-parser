#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "json_parser.h"

void test_testing(void)
{
	assert(true);
}

void test_valid(char *fname)
{
	FILE *f = fopen(fname, "r");
	if (f == NULL) {
		perror("fopen");
		exit(1);
	}
	
	fseek(f, 0L, SEEK_END);
	long fsize = ftell(f);
	rewind(f);

	char *buf = malloc(fsize + 1);
	fread(buf, fsize, 1, f);
	buf[fsize] = '\0';

	assert(is_valid_json(buf));
	
	fclose(f);
	free(buf);
}

int main(void)
{
	test_testing();

	test_valid("test_cases/step1/valid.json");

	printf("All tests passed!\n");
	return 0;
}
