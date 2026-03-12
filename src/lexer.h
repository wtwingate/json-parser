#pragma once

#include "token.h"
#include <stdlib.h>

typedef struct {
    char *input;
    size_t len;
    size_t pos;
    size_t read_pos;
    char c;
} Lexer;

Lexer new_lexer(char *input);
Token lexer_next_token(Lexer *l);
void lexer_skip_whitespace(Lexer *l);
void lexer_read_char(Lexer *l);
char lexer_peek_char(Lexer *l);
char *lexer_read_string(Lexer *l);
