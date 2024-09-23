#define FALSE 0
#define TRUE  1

typedef struct Token {
	int symbol;
	char *value;
} token_t;

enum symbols {
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

token_t *tokenize(char *s, int *array_len);
int is_valid_json(char *s);
