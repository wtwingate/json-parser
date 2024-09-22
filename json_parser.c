#include <stdbool.h>
#include <stdlib.h>

struct token {
	char *name;
	char *value;
};

enum token_names {
	BEGIN_ARRAY,
	BEGIN_OBJECT,
	END_ARRAY,
	END_OBJECT,
	NAME_SEP,
	VALUE_SEP,
	STRING,
	NUMBER,
	LITERAL
};

bool is_valid_json(char *s)
{
	if (s)
		return true;

	return false;
}
