#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

void test_testing(void)
{
	assert(TRUE);
}

void test_valid_json(char *fname)
{
	printf("Testing valid JSON: %s\n", fname);
        char *s = read_file(fname);
	assert(is_valid_json(s));
	free(s);
}

void test_invalid_json(char *fname)
{
	printf("Testing invalid JSON: %s\n", fname);
        char *s = read_file(fname);
	assert(!is_valid_json(s));
	free(s);
}

int main(void)
{
	test_testing();

	test_valid_json("test_cases/step1/valid.json");
	test_invalid_json("test_cases/step1/invalid.json");

	printf("All tests passed!\n");
	return 0;
}
