#include <ctype.h>
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
	int t_idx = 0;
	token_t *t_array = malloc(sizeof(token_t) * MAXSIZE);

	for (int i = 0; s[i] != '\0'; i++) {
		if (t_idx > MAXSIZE) {
			printf("Error: token array exceeds max size");
			return NULL;
		}

		switch (s[i]) {
			case '{':
				t_array[t_idx].symbol = BEGIN_OBJECT;
				t_array[t_idx].value = "{";
				t_idx++;
				break;
			case '}':
				t_array[t_idx].symbol = END_OBJECT;
				t_array[t_idx].value = "}";
				t_idx++;
				break;
			case ':':
				t_array[t_idx].symbol = NAME_SEP;
				t_array[t_idx].value = ":";
				t_idx++;
				break;
			case ',':
				t_array[t_idx].symbol = VALUE_SEP;
				t_array[t_idx].value = ",";
				t_idx++;
				break;
			case '"':
				{
					i++;
					int j = i;
					while (s[j] != '"')
						j++;
					int s_len = j - i;
					char *substr = malloc(s_len);
					memcpy(substr, s + i, s_len);
					substr[s_len] = '\0';
					t_array[t_idx].symbol = STRING;
					t_array[t_idx].value = substr;
					i = j;
					t_idx++;
					break;
				}
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				if (!isspace(s[i - 1]))
					break;

				{
					int j = i;
					while (isdigit(s[j]))
						j++;
					int s_len = j - i;
					char *substr = malloc(s_len);
					memcpy(substr, s + i, s_len);
					substr[s_len] = '\0';
					t_array[t_idx].symbol = NUMBER;
					t_array[t_idx].value = substr;
					i = j;
					t_idx++;
					break;
				}
			default:
				if (!strncmp("true", s + i, 4)) {
					t_array[t_idx].symbol = LITERAL;
					t_array[t_idx].value = "true";
					i += 3;
					t_idx++;
				} else if (!strncmp("false", s + i, 5)) {
					t_array[t_idx].symbol = LITERAL;
					t_array[t_idx].value = "false";
					i += 4;
					t_idx++;
				} else if (!strncmp("null", s + i, 4)) {
					t_array[t_idx].symbol = LITERAL;
					t_array[t_idx].value = "null";
					i += 3;
					t_idx++;
				}
				break;
		}
	}

	*array_len = t_idx;
	return t_array;
}

void print_token_array(token_t *t_array, int array_len)
{
	for (int i = 0; i < array_len; i++) {
		printf("symbol: %d | value: %s\n",
				t_array[i].symbol,
				t_array[i].value);
	}
}

int is_valid_json(char *s)
{
	printf("JSON string: %s\n", s);

	if (strlen(s) == 0)
		return FALSE;

	int array_len = 0;
	token_t *t_array = tokenize(s, &array_len);

	int objects = 0;

	print_token_array(t_array, array_len);

	for (int i = 0; i < array_len; i++) {
		if (objects < 0) {
			return FALSE;
		}

		switch (t_array[i].symbol) {
			case BEGIN_OBJECT:
				objects++;
				break;
			case END_OBJECT:
				objects--;
				break;
			case NAME_SEP:
				if (t_array[i - 1].symbol != STRING) {
					return FALSE;
				}
				if (t_array[i + 1].symbol != BEGIN_OBJECT &&
						t_array[i + 1].symbol != BEGIN_ARRAY &&
						t_array[i + 1].symbol != NUMBER &&
						t_array[i + 1].symbol != STRING &&
						t_array[i + 1].symbol != LITERAL) {
					return FALSE;
				}
				break;
			case VALUE_SEP:
				if (t_array[i - 1].symbol == BEGIN_OBJECT ||
						t_array[i - 1].symbol == BEGIN_ARRAY) {
					return FALSE;
				}
				if (t_array[i + 1].symbol == END_OBJECT ||
						t_array[i + i].symbol == END_ARRAY) {
					return FALSE;
				}
				break;
			default:
				/* return FALSE; */
				break;
		}
	}

	free(t_array);

	if (objects == 0) {
		return TRUE;
	} else {
		return FALSE;
	}
}
