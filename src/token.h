#pragma once

typedef enum TokenType {
  TOKEN_ILLEGAL,
  TOKEN_EOF,
  TOKEN_BEGIN_ARRAY,
  TOKEN_BEGIN_OBJECT,
  TOKEN_END_ARRAY,
  TOKEN_END_OBJECT,
  TOKEN_NAME_SEPARATOR,
  TOKEN_VALUE_SEPARATOR,
  TOKEN_NUMBER,
  TOKEN_STRING,
  TOKEN_LITERAL
} TokenType;

typedef struct Token {
  TokenType type;
  char *literal;
} Token;

Token new_token(TokenType type, char *literal);
void free_token(Token *t);
char *token_type_name(TokenType type);
