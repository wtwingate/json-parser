#include "token.h"
#include <stdlib.h>
#include <string.h>

Token new_token(TokenType type, char *literal) {
  char *copy = strndup(literal, strlen(literal));

  Token token = {
      .type = type,
      .literal = copy,
  };

  return token;
}

void free_token(Token *t) { free(t->literal); }

char *token_type_name(TokenType tt) {
  switch (tt) {
  case TOKEN_ILLEGAL:
    return "TOKEN_ILLEGAL";
  case TOKEN_EOF:
    return "TOKEN_EOF";
  case TOKEN_BEGIN_ARRAY:
    return "TOKEN_BEGIN_ARRAY";
  case TOKEN_BEGIN_OBJECT:
    return "TOKEN_BEGIN_OBJECT:";
  case TOKEN_END_ARRAY:
    return "TOKEN_END_ARRAY";
  case TOKEN_END_OBJECT:
    return "TOKEN_END_OBJECT";
  case TOKEN_NAME_SEPARATOR:
    return "TOKEN_NAME_SEPARATOR";
  case TOKEN_VALUE_SEPARATOR:
    return "TOKEN_VALUE_SEPARATOR";
  case TOKEN_NUMBER:
    return "TOKEN_NUMBER";
  case TOKEN_STRING:
    return "TOKEN_STRING";
  case TOKEN_LITERAL:
    return "TOKEN_LITERAL";
  default:
    return "Unknown";
  }
}
