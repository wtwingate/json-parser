#define FALSE 0
#define TRUE  1

struct token {
	int symbol;
	char *value;
};

enum t_symbols {
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

struct token *tokenizer(char *s, int *out_len);
int is_valid_json(char *s);
