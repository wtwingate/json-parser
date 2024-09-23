#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

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

	if (objects == 0) {
		return TRUE;
	} else {
		return FALSE;
	}
}
