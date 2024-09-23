#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

char *read_file(char *fname)
{
	FILE *file = fopen(fname, "r");
	if (!file) {
		perror("read_file -> fopen");
		return NULL;
	}
	
	fseek(file, 0, SEEK_END);
	long fsize = ftell(file);
	rewind(file);

	char *buf = malloc(fsize + 1);
	if (!buf) {
		perror("read_file -> malloc");
		fclose(file);
		return NULL;
	}
	
	size_t bytes_read = fread(buf, 1, fsize, file);
	if (bytes_read != (size_t) fsize) {
		perror("read_file -> fread");
		fclose(file);
		free(buf);
		return NULL;
	}
	
	buf[fsize] = '\0';
	fclose(file);
	return buf;
}

token_t *tokenize(char *s, int *array_len)
{
	int t_len = 8;
	int t_idx = 0;
	token_t *t_array = malloc(sizeof(token_t) * t_len);

	for (int i = 0; s[i] != '\0'; i++) {
		/* dynamically allocate token array */
		if (t_idx == t_len) {
			t_len *= 2;
			t_array = realloc(t_array, t_len);
		}

		switch (s[i]) {
		case '{':
			t_array[t_idx].symbol = BEGIN_OBJECT;
			t_array[t_idx].value = "{";
			break;
		case '}':
			t_array[t_idx].symbol = END_OBJECT;
			t_array[t_idx].value = "}";
			break;
		default:
			t_array[t_idx].symbol = -1;
			t_array[t_idx].value = "";
			break;
		}
		t_idx++;
	}

	*array_len = t_idx;
	return t_array;
}

int is_valid_json(char *s)
{
	printf("JSON string: %s\n", s);

	if (strlen(s) == 0)
		return FALSE;

	int t_len = 0;
	token_t *t_array = tokenize(s, &t_len);

	int objects = 0;

	for (int i = 0; i < t_len; i++) {
		printf("symbol: %d | value: %s\n",
		       t_array[i].symbol, t_array[i].value);

		if (objects < 0)
			return FALSE;

		switch (t_array[i].symbol) {
		case BEGIN_OBJECT:
			objects++;
			break;
		case END_OBJECT:
			objects--;
			break;
		default:
			return FALSE;
		}
	}

	free(t_array);

	if (objects == 0) {
		return TRUE;
	} else {
		return FALSE;
	}
}
