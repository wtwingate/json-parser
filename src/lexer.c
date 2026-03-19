#include "lexer.h"
#include "token.h"
#include <ctype.h>
#include <string.h>

Lexer new_lexer(char *input)
{
	Lexer lexer = {
	    .input = input,
	    .len = strlen(input),
	};

	lexer_read_char(&lexer);

	return lexer;
}

Token lexer_next_token(Lexer *l)
{
	Token token;

	lexer_skip_whitespace(l);

	switch (l->c) {
	case '[':
		token = new_token(TOKEN_BEGIN_ARRAY, "[");
		break;
	case '{':
		token = new_token(TOKEN_BEGIN_OBJECT, "{");
		break;
	case ']':
		token = new_token(TOKEN_END_ARRAY, "]");
		break;
	case '}':
		token = new_token(TOKEN_END_OBJECT, "}");
		break;
	case ':':
		token = new_token(TOKEN_NAME_SEPARATOR, ":");
		break;
	case ',':
		token = new_token(TOKEN_VALUE_SEPARATOR, ",");
		break;
	case '"': {
		char *literal = lexer_read_string(l);
		if (literal == NULL) {
			token = new_token(TOKEN_ILLEGAL, "");
		} else {
			token = new_token(TOKEN_STRING, literal);
		}
		free(literal);
		return token;
	}
	case '\0':
		token = new_token(TOKEN_EOF, "");
		break;
	default:
		if (isdigit(l->c) || l->c == '-') {
			char *literal = lexer_read_number(l);
			if (literal == NULL) {
				token = new_token(TOKEN_ILLEGAL, "");
			} else {
				token = new_token(TOKEN_NUMBER, literal);
			}
			free(literal);
			return token;
		} else if (isalpha(l->c)) {
			char *literal = lexer_read_literal(l);
			if (strcmp(literal, "true") == 0 ||
			    strcmp(literal, "false") == 0 ||
			    strcmp(literal, "null") == 0) {
				token = new_token(TOKEN_LITERAL, literal);
			} else {
				token = new_token(TOKEN_ILLEGAL, "");
			}
			free(literal);
			return token;
		} else {
			token = new_token(TOKEN_ILLEGAL, "");
		}
		break;
	}

	lexer_read_char(l);

	return token;
}

void lexer_skip_whitespace(Lexer *l)
{
	while (l->c == ' ' || l->c == '\t' || l->c == '\n' || l->c == '\r') {
		lexer_read_char(l);
	}
}

void lexer_read_char(Lexer *l)
{
	if (l->read_pos >= l->len) {
		l->c = '\0';
	} else {
		l->c = l->input[l->read_pos];
	}

	l->pos = l->read_pos;
	l->read_pos++;
}

char lexer_peek_char(Lexer *l)
{
	if (l->read_pos >= l->len) {
		return '\0';
	} else {
		return l->input[l->read_pos];
	}
}

char *lexer_read_string(Lexer *l)
{
	size_t start_pos = l->pos;

	lexer_read_char(l);

	while (l->c != '"' && l->c != '\0') {
		if (l->c == '\\') {
			char p = lexer_peek_char(l);
			if (p == '"' || p == '\\') {
				lexer_read_char(l);
			}
		}
		lexer_read_char(l);
	}

	if (l->c == '\0') {
		return NULL;
	}

	size_t len = l->read_pos - start_pos;
	char *string = malloc(len + 1);
	memcpy(string, l->input + start_pos, len);
	string[len] = '\0';

	lexer_read_char(l); // consume closing quote

	return string;
}

char *lexer_read_number(Lexer *l)
{
	if (l->c == '-' && !isdigit(lexer_peek_char(l))) {
		return NULL;
	}

	size_t start_pos = l->pos;

	lexer_read_char(l);

	while (isdigit(l->c) || l->c == '.') {
		lexer_read_char(l);
	}

	size_t len = l->pos - start_pos;
	char *number = malloc(len + 1);
	memcpy(number, l->input + start_pos, len);
	number[len] = '\0';
	return number;
}

char *lexer_read_literal(Lexer *l)
{
	size_t start_pos = l->pos;

	lexer_read_char(l);

	while (isalpha(l->c)) {
		lexer_read_char(l);
	}

	size_t len = l->pos - start_pos;
	char *literal = malloc(len + 1);
	memcpy(literal, l->input + start_pos, len);
	literal[len] = '\0';
	return literal;
}
