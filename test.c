#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

void test_testing(void)
{
	assert(TRUE);
}

void test_valid(char *fname)
{
	printf("Testing valid JSON: %s\n", fname);
	
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

void test_invalid(char *fname)
{
	printf("Testing invalid JSON: %s\n", fname);
	
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

	assert(!is_valid_json(buf));
	
	fclose(f);
	free(buf);
}

int main(void)
{
	test_testing();

	test_valid("test_cases/step1/valid.json");
	test_invalid("test_cases/step1/invalid.json");

	printf("All tests passed!\n");
	return 0;
}
