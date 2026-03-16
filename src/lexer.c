#include "lexer.h"
#include "token.h"
#include <string.h>

Lexer new_lexer(char *input) {
  Lexer lexer = {
      .input = input,
      .len = strlen(input),
  };

  lexer_read_char(&lexer);

  return lexer;
}

Token lexer_next_token(Lexer *l) {
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
  case '"':
    token = new_token(TOKEN_STRING, lexer_read_string(l));
    break;
  case '\0':
    token = new_token(TOKEN_EOF, "");
    break;
  default:
    token = new_token(TOKEN_ILLEGAL, "");
  }

  lexer_read_char(l);

  return token;
}

void lexer_skip_whitespace(Lexer *l) {
  while (l->c == ' ' || l->c == '\t' || l->c == '\n' || l->c == '\r') {
    lexer_read_char(l);
  }
}

void lexer_read_char(Lexer *l) {
  if (l->read_pos >= l->len) {
    l->c = '\0';
  } else {
    l->c = l->input[l->read_pos];
  }

  l->pos = l->read_pos;
  l->read_pos++;
}

char lexer_peek_char(Lexer *l) {
  if (l->read_pos >= l->len) {
    return '\0';
  } else {
    return l->input[l->read_pos];
  }
}

char *lexer_read_string(Lexer *l) {
  size_t start_pos = l->read_pos;

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

  size_t len = (l->pos - start_pos);

  return strndup(&l->input[start_pos], len);
}
