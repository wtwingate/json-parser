#include <stdlib.h>

#include "parser.h"

struct token *tokenizer(char *s, int *out_len)
{
	int t_len = 8;
	int t_idx = 0;
	struct token *t_array = malloc(sizeof(struct token) * t_len);

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
		}
	}

	*out_len = t_idx + 1;
	return t_array;
}

int is_valid_json(char *s)
{
	return FALSE;
}
